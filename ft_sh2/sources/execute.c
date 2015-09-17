/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/19 17:15:48 by anowak            #+#    #+#             */
/*   Updated: 2015/09/17 14:30:29 by anowak           ###   ########.fr       */
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

int		make_it_pipe(t_cmd *new, t_ftsh *sh, char ***env_dup)
{
	int	pipe_fd[2];
	int	child;

	printf("%d>>>> MAKING IT PIPE\n", getpid());
	if (pipe(pipe_fd))
		return (-1);
	child = fork();
	if (child == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (-1);
	}
	else if (child == 0)
	{
// PROCESSUS FILS
		printf("%d---- IM IN THE PIPED CHILD - %s\n", getpid(), ((t_cmd*)new->piped_to)->argv[0]);

		((t_cmd*)new->piped_to)->fd_out = pipe_fd[1];
//		printf("close returns %d\n", close(pipe_fd[0]));
		execute_command((new->piped_to), sh, env_dup);
	}
	else
	{
// PROCESSUS PARENT
		printf("%d---- iM THE PIPED FAZER - '%s'\n", getpid(), new->argv[0]);
		printf("%d---- i wait ...\n", getpid());
		wait4(0, NULL, 0, 0);
		printf("dup2 returns %d\n", dup2(pipe_fd[0], 0));
		printf("close(0) returns %d\n", close(0));	
		printf("close(pipeout) returns %d\n", close(pipe_fd[1]));
		printf("%d---- PIPED FATHER EXECUTES - '%s'\n", getpid(), new->argv[0]);
		execve(new->path, new->argv, *env_dup);
	}
	return (0);
}

void	do_the_fork_thing(t_cmd *new, char ***env_dup)
{
	int		ret;

	ret = 0;
	signal(SIGINT, SIG_DFL);
	signal(SIGINT, process_terminate_in_process);
	new->pid = fork();
	if (new->pid == -1)
		ft_putendl_fd("Error : Could'nt fork", 2);
	else if (new->pid == 0)
	{
// PROCESSUS FILS
		ret = execve(new->path, new->argv, *env_dup);
		if (ret == -1)
		{
			ft_putendl_fd("Error : Could'nt execute command", 2);
			print_ret_message(new->status, new->argv[0]);
		}
	}
	else
	{
// PROCESSUS PARENT
		if ((ret = wait(&(new->status))) == -1)
			ft_putendl_fd("Error : Wait returned -1", 2);
		print_ret_message(new->status, new->argv[0]);
	}
	return ;
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

	printf("%d---- EXECUTING COMMAND '%s'\n", getpid(), new->argv[0]);
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
			do_the_fork_thing(new, env_dup);
	}

	if (new->path)
		free(new->path);
	ft_tabfree(new->argv);
	return (ret);
}
