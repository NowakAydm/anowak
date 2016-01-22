/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/29 19:00:08 by anowak            #+#    #+#             */
/*   Updated: 2016/01/22 20:12:41 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	increment_shlvl(char ***env)
{
	int		n;
	char	**str;

	if (get_in_env(*env, "SHLVL"))
	{
		n = ft_atoi(get_in_env(*env, "SHLVL"));
		str = ft_memalloc(sizeof(char*) * 3);
		str[0] = ft_strdup("setenv");
		str[1] = ft_strnew(20);
		str[1] = ft_strcat(str[1], "SHLVL=");
		str[1] = ft_strcat(str[1], ft_itoa(++n));
		builtin_setenv(str, env);
		ft_tabfree(str);
	}
}

char	*remove_char(char *str, char c)
{
	char	*new;
	char	*spot;

	if (ft_strchr(str + 1, c))
	{
		new = ft_strdup(str + 1);
		while ((spot = ft_strchr(new, c)))
		{
			*spot = '\0';
			ft_strcat(new, spot + 1);
			spot = NULL;
		}
		spot = ft_strdup(new);
		free(new);
		return (spot);
	}
	return (str);
}

int		pipe_the_child(t_cmd *cmd, t_ftsh *sh, char ***env_dup, int *pipe_des)
{
	dup2(pipe_des[1], 1);
	close(pipe_des[0]);
	if (process_command(cmd->piped_to, sh))
		return (-1);
	redirect_output(cmd->piped_to);
	if ((cmd->piped_to)->piped_to)
		pipe_it_up(cmd->piped_to, sh, env_dup);
	redirect_fd(cmd->piped_to);
	if ((cmd->piped_to)->fd_out)
		do_the_fork_thing(cmd->piped_to, sh, env_dup);
	if (!redirect_input(cmd->piped_to))
		dup2((cmd->piped_to)->fd_in, 0);
	else
		exit(1);
	execve((cmd->piped_to)->path, (cmd->piped_to)->argv, *env_dup);
	return (0);
}

void	pipe_the_parent(t_cmd *cmd, char ***env_dup, int *pipe_des)
{
	dup2(pipe_des[0], 0);
	close(pipe_des[1]);
	if (cmd->fd_out)
		close((cmd->piped_to)->fd_out);
	if ((cmd->piped_to)->heredoc)
	{
		close((cmd->piped_to)->heredoc_pipe[0]);
		close((cmd->piped_to)->heredoc_pipe[1]);
	}
	redirect_output(cmd);
	wait(NULL);
	redirect_fd(cmd);
	if (cmd->fd_out)
		dup2(cmd->fd_out, 1);
	if (cmd->input_file || cmd->heredoc)
		print_input_redirection_error(cmd);
	execve(cmd->path, cmd->argv, *env_dup);
}

int		pipe_it_up(t_cmd *cmd, t_ftsh *sh, char ***env_dup)
{
	pid_t	child;
	int		pipe_des[2];

	if (pipe(pipe_des))
		return (-1);
	child = fork();
	if (child == -1)
	{
		close(pipe_des[0]);
		close(pipe_des[1]);
		return (-1);
	}
	else if (child == 0)
		if (pipe_the_child(cmd, sh, env_dup, pipe_des))
			return (-1);
	pipe_the_parent(cmd, env_dup, pipe_des);
	return (0);
}
