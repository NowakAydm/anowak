/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/19 17:15:48 by anowak            #+#    #+#             */
/*   Updated: 2015/05/26 19:12:27 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int		find_path_to_command(t_cmd *new, char **path_dir)
{
	int	x = -1;

	printf(">>>> Find path to command STARTS\n");
	if (!(new->path = ft_strnew(MAXPATHLEN)))
		return (0);
	if (new->argv[0][0] == '.' || new->argv[0][0] == '/')
	{
		ft_strcpy(new->path, new->argv[0]);
		printf("---- checking if executable here | path = %s\n", new->path);
		if (!(access(new->path, F_OK)))
		{
			printf("---- All goooood ! path = %s\n", new->path);
			return (1);
		}		
		printf("---- nope ... path = %s\n", new->path);
	}
	else
		while (path_dir[++x])
		{
			printf("---- searching '%s' in %s\n", new->argv[0], path_dir[x]);
			ft_strcpy(new->path, path_dir[x]);
			ft_strcat(new->path, "/");
			ft_strcat(new->path, new->argv[0]);
			printf("---- path = |%s|\n", new->path);
			if (!(access(new->path, F_OK)))
			{
				printf("---- found it ! path = %s\n", new->path);
				if ((access(new->path, X_OK)))
				  {
				    printf("---- Error : permission denied: path = %s\n", new->path);
				    return (-1);
				  }
				return (1);
			}
			ft_strclr(new->path);
			printf("---- nope ... path = %s\n", new->path);
		}
	return (-1);
}

void	print_ret_message(int status, char *cmd)
{
	if (status)
	{
		ft_putstr(cmd);
		ft_putstr(" : ");
		if (status == SIGQUIT)
			printf("quit program\n");
		else if (status == SIGSTOP || status == SIGTSTP)
			printf("process stopped\n");
		else if (status == SIGKILL)
			printf("kill program\n");
		else if (status == SIGBUS)
			printf("bus error\n");
		else if (status == SIGSEGV)
			printf("segmentation fault\n");
		else if (status == SIGSYS)
			printf("unknown system call\n");
		else if (status == SIGILL)
			printf("illegal instruction\n");
	}
}

void	execute_command_line(char *line, char **path_dir, char ***env_dup)
{
	t_cmd	*new = NULL;
	int		ret = 0;
	
	printf(">>>> EXECUTE COMMAND LINE STARTS\n");
	if (!(new = process_command_line(line)))
	{
		printf("<<<< process_command_line FAILED\n");
		return ;
	}
	if (check_builtin(new, env_dup))
	  {
	    ft_strcpy(new->path, new->argv[0]);
	    return ;
	  }
	if (!(ret = find_path_to_command(new, path_dir)))
		printf("---- Error : could'nt allocate enough memory\n");
	else
	{
		if (ret < 0)
			printf("---- Error : command not found\n");
		else
		{
			printf("---- Command FOUND :\npath = |%s|\n", new->path);
			ret = 0;
			if ((new->pid = fork()) > 0)
			{
				printf("---- Fork forked | pid = %d\n", new->pid);

				if ((ret = wait(&(new->status))) == -1)
					printf("---- wait returned -1\n");
				else if (ret)
					printf("---- Wait finished | pid = %d | status = %d\n", new->pid, new->status);
				print_ret_message(new->status, new->argv[0]);
			}
			else if (new->pid == 0)
			{
				printf("---- Executing %s   |   cur  pid = %d", new->path, getpid());
				ret = execve(new->path, new->argv, *env_dup);
			}
			else if (new->pid == -1)
				printf("XXXX Error : Could'nt fork\n");
		}
	}
	printf("<<<<\n");
	return;
}
