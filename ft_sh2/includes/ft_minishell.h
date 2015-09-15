/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/19 14:41:22 by anowak            #+#    #+#             */
/*   Updated: 2015/09/15 12:58:29 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

# include <stdio.h>

# include <sys/types.h>
# include <sys/param.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <unistd.h>

# include "../libft/includes/libft.h"
# include "structs.h"

# define PROMPT "$> "

typedef struct stat     t_stat;

/*
**\ -------   ft_minishell1.c   --------
*/
char	*get_in_env(char **envp, char *var);
char	**extract_path_directories(char **envp);
t_ftsh	*initialize_sh(int argc, char **argv, char **envp);

/*
** -------      signals.c      --------
*/
void	process_terminate_in_sh(int signum);
void	process_terminate_in_process(int signum);
void	process_buserr(int signum);
void	process_segfault(int signum);
void	catch_signals(void);

/*
** -------      execute.c      --------
*/
int		check_permissions(char *path);
int		find_path_to_command(t_cmd *new, char **path_dir);
void	print_ret_message(int status, char *cmd);
void	do_the_fork_thing(t_cmd *new, char ***env_dup);
int		execute_command(t_cmd *new, t_ftsh *sh, char ***env_dup);

/*
** -------    command_line.c   --------
*/
char	*recover_previous_line(char **line, char **tmp);
char	*get_command_line(void);
t_list	*add_to_command_list(t_list *list, t_list *args, int pipe);
t_list	*process_command_line(char *line, char ***env_dup, int ret);
int		execute_command_line(t_ftsh *sh, char ***env_dup);

/*
** -------      arguments.c    --------
*/
int		argument_is_in_quotes(char *line, t_list **list, int x);
int		argument_not_in_quotes(char *line, t_list **list, int x);
t_list	*split_into_args(char *line, char ***env, int ret);

/*
** -------       quotes.c      --------
*/
int		check_pipe(char *line);
int		prompt_missing_quote(int ret);
int		check_quotes_in_line(char *line);
int		dist_to_next_quote(char *line, int c);

/*
** -------      builtins.c     --------
*/
int		change_env_pwd(char ***envp);
int		check_if_in_env(char *av, char **env);
int		builtin_exit(int ac, char **av);
int		builtin_cd(char **av, char ***envp);
int		builtin_setenv(char **av, char ***env);
int		builtin_unsetenv(char **av, char ***env);
int		builtin_env(char **env);
int		check_builtin(t_cmd *cmd, char ***envp);

#endif
