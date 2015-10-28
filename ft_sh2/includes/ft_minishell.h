/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/19 14:41:22 by anowak            #+#    #+#             */
/*   Updated: 2015/10/28 14:57:10 by AdamNowak        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

# include "../libft/includes/libft.h"
# include "structs.h"

# include <stdio.h>

# include <sys/types.h>
# include <sys/param.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <unistd.h>
# include <fcntl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# undef tab


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
int		do_the_fork_thing(t_cmd *new, t_ftsh *sh, char ***env_dup);
int		process_command(t_cmd *new, t_ftsh *sh);
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
int		arg_is_fd_redirector(char *arg);
char	*remove_char(char *str, char c);

/*
** -------       quotes.c      --------
*/
int		check_parenthesis(char *line);
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
int		execute_builtin(t_cmd *cmd, char ***envp);
int		check_builtin(t_cmd *cmd);

/*
** -------      term.c     --------
*/
void	restore_term(struct termios *term);
int		initialize_term(t_ftsh *sh, char **envp);


#endif
