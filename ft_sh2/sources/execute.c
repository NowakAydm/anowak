/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/19 17:15:48 by anowak            #+#    #+#             */
/*   Updated: 2015/09/15 13:03:55 by anowak           ###   ########.fr       */
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
	}
}

int		make_the_pipe(t_cmd *new)
{
	int fildes[2];

	ft_putendl("CREATING PIPE");
	if (pipe(fildes))
		return (1);
	if ((new->fd_out = dup2(1, fildes[1])) == -1)
		ft_putendl_fd("Error : dup returned -1", 2);
	new->pipeout = fildes[0];
	ft_putstr("DUPLICATED OUT FD = ");
	ft_putnbr(new->fd_out);
	ft_putendl("");
	ft_putstr("PIPE OUT FD = ");
	ft_putnbr(new->pipeout);
	ft_putendl("");

//	if ((ret = close(1)) == -1)
//		ft_putendl_fd("Error : close(1) returned -1", 2);
	return (0);
}

void	do_the_fork_thing(t_cmd *new, char ***env_dup)
{
	int		ret;

	ret = 0;
	signal(SIGINT, SIG_DFL);
	signal(SIGINT, process_terminate_in_process);
	if ((new->pid = fork()) > 0)
	{
		if ((ret = wait(&(new->status))) == -1)
			ft_putendl_fd("Error : Wait returned -1", 2);
		print_ret_message(new->status, new->argv[0]);
	}
	else if (new->pid == 0)
	{
		if (new->pipeout)
			if (make_the_pipe(new))
			{
				ft_putendl_fd("Error : could'nt pipe", 2);
				return ;
			}
		if (new->pipein)
		{
			if ((new->pipein = dup2(0, new->pipein)) == -1)
			{
				ft_putendl_fd("Error : dup returned -1", 2);
				return ;
			}
			if ((ret = close(0)) == -1)
				ft_putendl_fd("Error : close(0) returned -1", 2);
		}
		ft_putstr_fd("EXECUTING COMMAND = ", 1);
		ft_putendl_fd(new->argv[0], 1);
		ret = execve(new->path, new->argv, *env_dup);
	}
	else if (new->pid == -1)
		ft_putendl_fd("Error : Could'nt fork", 2);
	return ;
}

int		execute_command(t_cmd *new, t_ftsh *sh, char ***env_dup)
{
	int		ret;

	if ((ret = check_builtin(new, env_dup)))
	{
		ft_tabfree(new->argv);
		return (ret - 1);
	}
	if (!(ret = find_path_to_command(new, sh->path_dir)))
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
		do_the_fork_thing(new, env_dup);
	free(new->path);
	ft_tabfree(new->argv);
	return (ret);
}
