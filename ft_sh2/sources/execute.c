/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/19 17:15:48 by anowak            #+#    #+#             */
/*   Updated: 2015/10/14 20:23:14 by anowak           ###   ########.fr       */
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

int		redirect_input(t_cmd *cmd)
{
	int		ret;
	char	*str;
	t_list	*tmp;

	ret = 1;
	str = NULL;
	cmd->fd_in = 0;
	if (cmd->input_file)
	{
		cmd->fd_in = open(cmd->input_file, O_RDONLY);
		if (cmd->fd_in == -1)
		{
			ft_putstr_fd("Error : can't open file : ", 2);
			ft_putendl_fd(cmd->input_file, 2);			
			return (-1);
		}
	}
	if (cmd->heredoc)
	{
		pipe(cmd->heredoc_pipe);
		if (cmd->fd_in)
			dup2(cmd->fd_in, cmd->heredoc_pipe[0]);
		else
			cmd->fd_in = cmd->heredoc_pipe[0];
		tmp = cmd->heredoc_list;
		while (tmp)
		{
			write(cmd->heredoc_pipe[1], tmp->content, ft_strlen(tmp->content));
			write(cmd->heredoc_pipe[1], "\n", 1);
			tmp = tmp->next;
		}
		close(cmd->heredoc_pipe[1]);
	}
	return (0);
}

int		redirect_output(t_cmd *cmd)
{
	int		fd;

	fd = 0;
	if (cmd->out || cmd->out_append)
	{
		cmd->fd_out = 1;
		if (cmd->out)
		{
			if ((fd = open((cmd->out)->content, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
			{
				ft_putstr_fd("Error : can't write output to file : ", 2);
				ft_putendl_fd((cmd->out)->content, 2);
			}
			ft_lstdel(&cmd->out, ft_lstdelcontent);
		}
		else if (cmd->out_append)
		{
			if ((fd = open((cmd->out_append)->content, O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1)
			{
				ft_putstr_fd("Error : can't write output to end of file : ", 2);
				ft_putendl_fd((cmd->out_append)->content, 2);
			}
			ft_lstdel(&cmd->out_append, ft_lstdelcontent);
		}
		cmd->fd_out = fd;
	}
	return (0);
}

void	print_input_redirection_error(t_cmd *cmd)
{
	ft_putstr_fd("Error : ", 2);
	ft_putstr_fd(cmd->argv[0], 2);
	if (cmd->input_file)
	{
		ft_putstr_fd(" < ", 2);			
		ft_putstr_fd(cmd->input_file, 2);
	}
	else
	{
		ft_putstr_fd(" << ", 2);			
		ft_putstr_fd(cmd->heredoc, 2);
	}
	ft_putendl_fd(" : can't redirect input of a piped command", 2);
}

void	redirect_fd(t_cmd *cmd)
{
	t_list	*tmp;

	tmp = cmd->to_redirect;
	while (tmp)
	{
		if (cmd->out || cmd->out_append || cmd->piped_to)
			ft_putendl_fd("Error : cannot redirect output", 2);
		else
			printf("Redirecting '%d' to '%d' returns %d\n", *(char*)tmp->content - 48, *((char *)(tmp->content) + 3) - 48, dup2( *((char *)(tmp->content) + 3) - 48, (*(char*)tmp->content - 48)));
		tmp = tmp->next;
		if (tmp)
			tmp = tmp->next;
	}	
	tmp = cmd->to_close;
	while (tmp)
	{
		printf("Closing '%d' returns %d\n", *(char*)tmp->content - 48, close((*(char*)tmp->content) - 48));
		tmp = tmp->next;
	}
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
	{
// PROCESSUS FILS
		dup2(pipe_des[1], 1);
		close(pipe_des[0]);

		if (process_command(cmd->piped_to, sh))
			return (-1);
		if ((cmd->piped_to)->piped_to)
			pipe_it_up(cmd->piped_to, sh, env_dup);

		redirect_output(cmd->piped_to);
		redirect_fd(cmd->piped_to);
		if ((cmd->piped_to)->fd_out)
		{
//			(cmd->piped_to)->piped_to = NULL;
			do_the_fork_thing(cmd->piped_to, sh, env_dup);
		}

		if (!redirect_input(cmd->piped_to))
			dup2((cmd->piped_to)->fd_in, 0);
		else
			exit(1);

		execve((cmd->piped_to)->path, (cmd->piped_to)->argv, *env_dup);

		return (0);
	}
	
// PROCESSUS PARENT
	
	dup2(pipe_des[0], 0);
	close(pipe_des[1]);
	if (cmd->fd_out)
		close((cmd->piped_to)->fd_out);
	if ((cmd->piped_to)->heredoc)
	{
		close((cmd->piped_to)->heredoc_pipe[0]);
		close((cmd->piped_to)->heredoc_pipe[1]);
	}

	wait(NULL);

	redirect_output(cmd);
	redirect_fd(cmd);
	if (cmd->fd_out)
		dup2(cmd->fd_out, 1);

	if (cmd->input_file || cmd->heredoc)
		print_input_redirection_error(cmd);

/* Comment this to unable input redirections on piped commands
	t_cmd	*tmp;

	if (cmd->input_file || cmd->heredoc)
	{
		tmp = cmd->piped_to;
		cmd->piped_to = NULL;
		if (cmd->out)
		{
			cmd->out_append = cmd->out;
			cmd->out = NULL;
		}
		do_the_fork_thing(cmd, sh, env_dup);		
		cmd->piped_to = tmp;		
	}
//*/
	execve(cmd->path, cmd->argv, *env_dup);

	return (0);
}

int		do_the_fork_thing(t_cmd *new, t_ftsh *sh, char ***env_dup)
{
	int		ret;

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
			if (new->fd_out)
				dup2(new->fd_out, 1);			
//			if (new->heredoc)
//				dup2(new->heredoc_pipe[0], 0);				
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
	}
	else
	{
// PROCESSUS PARENT
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
	}
	return (0);
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
			ret = do_the_fork_thing(new, sh, env_dup);
	}

	if (new->path)
		free(new->path);
	ft_tabfree(new->argv);
	return (ret);
}
