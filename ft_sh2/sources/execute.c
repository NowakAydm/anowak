/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/19 17:15:48 by anowak            #+#    #+#             */
/*   Updated: 2015/09/22 15:15:32 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int		check_permissions(char *path)
{
	t_stat *s;

	if (!(s = (t_stat*)ft_memalloc(sizeof(t_stat))))
		return (0);
	if (lstat(path, s))
		if (stat(path, s))
		{
			if (s)
				free(s);
			return (-1);
		}
	if (S_ISDIR(s->st_mode))
	{
		free(s);
		return (-2);
	}
	free(s);
	if (!(access(path, F_OK)))
	{
		if ((access(path, X_OK)))
			return (-2);
		return (1);
	}
	return (-1);
}

int		find_path_to_command(t_cmd *new, char **path_dir)
{
	int	x;

	x = -1;
	if (!(new->path = ft_strnew(MAXPATHLEN)))
		return (0);
	if (new->argv[0][0] == '.' || new->argv[0][0] == '/')
	{
		ft_strcpy(new->path, new->argv[0]);
		return (check_permissions(new->path));
	}
	else if (path_dir)
	{
		while (path_dir[++x])
		{
			ft_strcpy(new->path, path_dir[x]);
			ft_strcat(new->path, "/");
			ft_strcat(new->path, new->argv[0]);
			if (check_permissions(new->path) != -1)
				return (check_permissions(new->path));
			ft_strclr(new->path);
		}
	}
	return (-1);
}

void	print_ret_message(int status, char *cmd)
{
	if (status && status <= 31 && status > 0)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(" : ", 2);
		ft_putnbr_fd(status, 2);
		ft_putstr_fd(" : ", 2);
		if (status == SIGINT)
			ft_putendl_fd("process interrupted", 2);
		else if (status == SIGQUIT)
			ft_putendl_fd("process aborted", 2);
		else if (status == SIGSTOP || status == SIGTSTP)
			ft_putendl_fd("process stopped", 2);
		else if (status == SIGKILL)
			ft_putendl_fd("kill program", 2);
		else if (status == SIGBUS)
			ft_putendl_fd("bus error", 2);
		else if (status == SIGSEGV)
			ft_putendl_fd("segmentation fault", 2);
		else if (status == SIGSYS)
			ft_putendl_fd("unknown system call", 2);
		else if (status == SIGILL)
			ft_putendl_fd("illegal instruction", 2);
		else
			ft_putendl_fd("something bad happened", 2);
	}
}

int		redirect_output(t_cmd *cmd)
{
	int		fd;
	t_list	*tmp;

	if (cmd->out || cmd->out_append)
	{
		while (cmd->out)
		{
//			printf("Duplicating out for file '%s'\n", (cmd->out)->content);
			fd = 0;
			if ((fd = open((cmd->out)->content, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
			{
			}
				ft_putstr_fd("Error : can't write output to file : ", 2);
				ft_putendl_fd((cmd->out)->content, 2);
//			printf("fd = %d\n", fd);
//			else
			ft_lstaddend(&(cmd->fd_out), ft_lstnew(&fd, sizeof(int)));
			tmp = cmd->out;
			cmd->out = (cmd->out)->next;
			ft_lstdelone(&tmp, ft_lstdelcontent);
		}
		while (cmd->out_append)
		{
//			printf("Duplicating out for file '%s'\n", (cmd->out_append)->content);
			fd = 0;
			if ((fd = open((cmd->out_append)->content, O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1)
			{
			}
				ft_putstr_fd("Error : can't write output to end of file : ", 2);
				ft_putendl_fd((cmd->out_append)->content, 2);
//			printf("fd = %d\n", fd);
//			else
			ft_lstadd(&(cmd->fd_out), ft_lstnew(&fd, sizeof(int)));
			tmp = cmd->out_append;
			cmd->out_append = (cmd->out_append)->next;
			ft_lstdelone(&tmp, ft_lstdelcontent);
		}
//		close(1);
	}
	return (0);
}

int		pipe_it_up(t_cmd *cmd, t_ftsh *sh, char ***env_dup)
{
	pid_t	child;
	int		pipe_des[2];
	t_list	*tmp;

	redirect_output(cmd->piped_to);
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
	{
// PROCESSUS FILS
		dup2(pipe_des[1], 1);
		close(pipe_des[0]);
		if (process_command(cmd->piped_to, sh))
			return (-1);
		if ((cmd->piped_to)->piped_to)
			pipe_it_up(cmd->piped_to, sh, env_dup);

		tmp = cmd->fd_out;
		while (tmp)
		{
			printf("dup2 return %d\n", dup2(*(int*)(tmp->content), 0));
			tmp = tmp->next;
		}
		execve((cmd->piped_to)->path, (cmd->piped_to)->argv, *env_dup);
		return (0);
	}
	
// PROCESSUS PARENT
	tmp = cmd->fd_out;
	while (tmp)
	{
		printf("close(%d) return %d\n",*(int*)(tmp->content), close(*(int*)(tmp->content)));
		tmp = tmp->next;
	}
	dup2(pipe_des[0], 0);
	close(pipe_des[1]);
	wait(NULL);
	redirect_output(cmd);
	execve(cmd->path, cmd->argv, *env_dup);
	return (0);
}

void	do_the_fork_thing(t_cmd *new, t_ftsh *sh, char ***env_dup)
{
	int		ret;
	t_list*	tmp;

	ret = 0;
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
	{
// PROCESSUS FILS
		if (new->piped_to)
			ret = pipe_it_up(new, sh, env_dup);
		else
		{
			tmp = new->fd_out;
			while (tmp)
			{
				printf("dup2(%d) return %d\n", *(int*)(tmp->content), dup2(*(int*)(tmp->content), 1));
				tmp = tmp->next;
			}
			ret = execve(new->path, new->argv, *env_dup);
		}
		if (ret == -1)
		{
			ft_putendl_fd("Error : Could'nt execute command", 2);
			print_ret_message(new->status, new->argv[0]);
		}
	}
	else
	{
// PROCESSUS PARENT
		tmp = new->fd_out;
		while (tmp)
		{
			printf("close(%d) return %d\n",*(int*)(tmp->content), close(*(int*)(tmp->content)));
			tmp = tmp->next;
		}
		if ((ret = wait(&(new->status))) == -1)
			ft_putendl_fd("Error : Wait returned -1", 2);
		print_ret_message(new->status, new->argv[0]);
	}
	return ;
}

int		process_command(t_cmd *new, t_ftsh *sh)
{
	int		ret;

	ret = 0;
	if ((ret = check_builtin(new)))
	{
		new->is_builtin = 1;
		return (0);
	}
	else if (!(ret = find_path_to_command(new, sh->path_dir)))
	{
		ft_putendl_fd("Error : could'nt allocate enough memory", 2);
		ret = 12;
	}
	else if (ret == -1)
	{
		ft_putstr_fd("Error : command not found : ", 2);
		ft_putendl_fd(new->argv[0], 2);
		ret = 127;
	}
	else if (ret < -1)
	{
		ft_putstr_fd("Error : permission denied : ", 2);
		ft_putendl_fd(new->argv[0], 2);
		ret = 126;
	}
	else
		return (0);
	return (ret);
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
//	TODO - REDIRECTIONS SUR LES BUILTINS
		if (new->is_builtin)
			ret = execute_builtin(new, env_dup) - 1;
		else
			do_the_fork_thing(new, sh, env_dup);
	}

	if (new->path)
		free(new->path);
	ft_tabfree(new->argv);
	return (ret);
}
