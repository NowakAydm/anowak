/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/19 17:15:48 by anowak            #+#    #+#             */
/*   Updated: 2016/01/22 17:51:53 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int		fork_the_child(t_cmd *new, t_ftsh *sh, char ***env_dup)
{
	int	ret;

	if (new->piped_to)
		ret = pipe_it_up(new, sh, env_dup);
	else
	{
		if (new->fd_out)
			dup2(new->fd_out, 1);
		if (!redirect_input(new))
			dup2(new->fd_in, 0);
		else
			return (1);
		redirect_fd(new);
		ret = execve(new->path, new->argv, *env_dup);
	}
	if (ret == -1)
	{
		ft_putendl_fd("Error : Could'nt execute command", 2);
		print_ret_message(new->status, new->argv[0]);
	}
	return (0);
}

int		do_the_fork_thing(t_cmd *new, t_ftsh *sh, char ***env_dup)
{
	int		ret;

	signal(SIGINT, SIG_DFL);
	signal(SIGTSTP, SIG_IGN);
	if (signal(SIGINT, process_terminate_in_process) == SIG_ERR)
		ft_putendl_fd("Error : can't catch signal", 2);
	if (!(new->piped_to))
		redirect_output(new);
	new->pid = fork();
	if (new->pid == -1)
		ft_putendl_fd("Error : Could'nt fork", 2);
	else if (new->pid == 0)
		if (fork_the_child(new, sh, env_dup))
			return (1);
	if (new->heredoc)
	{
		close(new->heredoc_pipe[0]);
		close(new->heredoc_pipe[1]);
	}
	if (new->fd_out)
		close(new->fd_out);
	if ((ret = wait(&(new->status))) == -1)
		ft_putendl_fd("Error : Wait returned -1", 2);
	print_ret_message(new->status, new->argv[0]);
	return (0);
}

int		process_command(t_cmd *new, t_ftsh *sh)
{
	int		ret;

	if ((ret = check_builtin(new)))
	{
		new->is_builtin = 1;
		return (0);
	}
	else if (!(ret = find_path_to_command(new, sh->path_dir)))
	{
		ft_putendl_fd("Error : could'nt allocate enough memory", 2);
		return (12);
	}
	else if (ret == -1)
	{
		ft_putstr_fd("Error : command not found : ", 2);
		ft_putendl_fd(new->argv[0], 2);
		return (127);
	}
	else if (ret < -1)
	{
		ft_putstr_fd("Error : permission denied : ", 2);
		ft_putendl_fd(new->argv[0], 2);
		return (126);
	}
	return (0);
}

int		execute_command(t_cmd *new, t_ftsh *sh, char ***env_dup)
{
	int		ret;

	if ((ret = process_command(new, sh)))
	{
		free(new->path);
		ft_tabfree(new->argv);
		return (ret);
	}
	else
	{
		if (new->is_builtin)
			ret = execute_builtin(new, env_dup) - 1;
		else
			ret = do_the_fork_thing(new, sh, env_dup);
	}
	if (new->path)
		free(new->path);
	ft_tabfree(new->argv);
	return (ret);
}

int		execute_command_line(t_ftsh *sh, char ***env_dup)
{
	t_list	*list;
	t_list	*tmp;
	int		ret;

	ret = 0;
	list = NULL;
	if (!(list = process_command_line(sh->line, env_dup, sh->ret)))
		return (1);
	while (list)
	{
		while (((t_cmd*)list->content)->pipe)
		{
			tmp = list->next;
			((t_cmd*)tmp->content)->piped_to = list->content;
			list = tmp;
		}
		ret = execute_command(list->content, sh, env_dup);
		tmp = list->next;
		ft_lstdelone(&list, ft_lstdelcontent);
		list = tmp;
	}
	return (ret);
}
