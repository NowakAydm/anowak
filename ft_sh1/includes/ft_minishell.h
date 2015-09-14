/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/19 14:41:22 by anowak            #+#    #+#             */
/*   Updated: 2015/07/12 16:10:55 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
#define FT_MINISHELL_H

#include <stdio.h>

#include <sys/types.h>
#include <sys/param.h>
#include <sys/uio.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>

#include "../libft/includes/libft.h"

#define PROMPT "$> "

typedef struct	s_cmd
{
	char		*path;
	int			argc;
	char		**argv;
	pid_t		pid;
	int			status;
}				t_cmd;

int		check_quotes_in_line(char *line);
char	*recover_previous_line(char **line, char **tmp);
char	*get_command_line(void);
char	**split_into_args(char *line);
t_cmd	*process_command_line(char *line);

void	execute_command_line(char *line, char **path_dir, char ***env_dup);

int		builtin_cd(char **av, char ***envp);
int		builtin_setenv(char **av, char ***env);
int		builtin_unsetenv(char **av, char ***env);
int		builtin_env(char **av, char **env);
int		check_builtin(t_cmd *cmd, char ***envp);

#endif
