/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/19 14:41:22 by anowak            #+#    #+#             */
/*   Updated: 2016/01/22 21:02:49 by anowak           ###   ########.fr       */
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
# include <time.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# undef tab

# define PROMPT "$> "
# define PROMPTLEN 3

typedef struct stat		t_stat;

/*
**\ -------     minishell.c    --------
*/
char	*get_in_env(char **envp, char *var);
char	**extract_path_directories(char **envp);
t_ftsh	*initialize_sh(int argc, char **argv, char **envp);
void	command_line_loop(t_ftsh *sh);

/*
** -------       signals.c      --------
*/
void	process_terminate_in_sh(int signum);
void	process_terminate_in_process(int signum);
void	process_buserr(int signum);
void	process_segfault(int signum);
void	catch_signals(void);

/*
** -------        pipe.c        --------
*/
void	increment_shlvl(char ***env);
char	*remove_char(char *str, char c);
int		pipe_the_child(t_cmd *cmd, t_ftsh *sh, char ***env_dup, int *pipe_des);
void	pipe_the_parent(t_cmd *cmd, char ***env_dup, int *pipe_des);
int		pipe_it_up(t_cmd *cmd, t_ftsh *sh, char ***env_dup);

/*
** -------       prints.c       --------
*/
void	print_input_redirection_error(t_cmd *cmd);
void	print_ret_message(int status, char *cmd);
int		write_prompt(char **prompt);
void	write_command_to_history(char *str, int fd);
void	write_to_history(char *str);

/*
** -------       dup_fd.c       --------
*/
void	redirect_from_heredoc(t_cmd *cmd);
int		redirect_input(t_cmd *cmd);
int		redirect_appending_output(char *s);
int		redirect_output(t_cmd *cmd);
void	redirect_fd(t_cmd *cmd);

/*
** -------      execute.c       --------
*/
int		fork_the_child(t_cmd *new, t_ftsh *sh, char ***env_dup);
int		do_the_fork_thing(t_cmd *new, t_ftsh *sh, char ***env_dup);
int		process_command(t_cmd *new, t_ftsh *sh);
int		execute_command(t_cmd *new, t_ftsh *sh, char ***env_dup);
int		execute_command_line(t_ftsh *sh, char ***env_dup);

/*
** -------     command_line.c   --------
*/
char	*recover_previous_line(char **line, char **tmp);
char	*get_command_line(void);
t_list	*add_to_command_list(t_list *list, t_list *args, int pipe);
int		process_argument(char *arg, t_list **cmds, t_list **new_cmd);
t_list	*process_command_line(char *line, char ***env_dup, int ret);

/*
** -------    redirections.c    --------
*/
t_list	*process_redirection(t_list *list, t_cmd *cmd);
int		get_heredoc(t_cmd *cmd);
void	add_input_redirection(t_cmd *cmd, char *arg);
void	add_output_redirection(t_cmd *cmd, char *arg);
int		arg_is_fd_redirector(char *arg);

/*
** -------      arguments.c     --------
*/
int		add_argument_to_list(char *line, t_list **list, int x, int y);
int		argument_not_in_quotes(char *line, t_list **list, int x);
void	replace_by_env_var(t_list *list, char **env, int ret);
void	replace_tilde(t_list *list, char **env);
t_list	*split_into_args(char *line, char ***env, int ret);

/*
** -------        checks.c      --------
*/
int		check_permissions(char *path);
int		check_everything(char *line);
int		check_quotes_in_line(char *line);
int		check_parenthesis(char *line);
int		check_pipe(char *line);

/*
** -------       quotes.c      --------
*/
int		argument_is_in_quotes(char *line, t_list **list, int x);
int		prompt_missing_quote(int ret);
int		dist_to_next_quote(char *line, int c);
int		find_path_to_command(t_cmd *new, char **path_dir);

/*
** -------      history.c     --------
*/
char	**get_history(char **history);
void	history_update_pos(int *pos, char **line);
void	replace_line_with_history(int *pos, char **line, char **h, int index);
void	navigate_through_history(char *key, int *pos, char **line);

/*
** -------   process_key.c  --------
*/
void	process_left_arrow_on_begl(int *pos);
void	process_left_arrow(int *pos, char **line);
void	process_right_arrow(int *pos, char **line);
void	process_alt_arrow(char *key, int *pos, char **line);
int		process_special_key(char *key, int *pos, char **line);

/*
** -------  move_cursor.c  --------
*/
void	go_up_aline(int *pos, char **line);
void	go_down_aline(int *pos, char **line);
void	go_to_endl(int *pos, char **line);
void	go_to_begl(int *pos, char **line);

/*
** -------   insert_char.c  --------
*/
int		process_copypaste(char *key, int *pos, char **line);
void	delete_char_up_aline(int *pos, char **line);
int		delete_char(int *pos, char **line);
void	insert_key(char *key, char **line, int *pos);

/*
** -------   read_line.c  --------
*/
int		read_next_char(char **line, int *pos);
void	clear_line(char **line);
int		read_next_line(char **line);
int		ft_outc(int c);
int		process_enter(char *key, char **line, int *pos);

/*
** -------   move_word.c   --------
*/
void	go_to_prevword(int *pos, char **line);
void	go_to_nextword(int *pos, char **line);

/*
** -------      term.c     --------
*/
void	restore_term(struct termios *term);
int		initialize_term(t_ftsh *sh, char **envp);
int		term_line_len(int n, char **line);
int		term_line_index(int *pos, char **line);
int		process_key(char *key, char **line, int *pos);

/*
** -------      builtins.c     --------
*/
int		execute_builtin(t_cmd *cmd, char ***envp);
int		check_builtin(t_cmd *cmd);

int		change_env_pwd(char ***envp);
int		check_if_in_env(char *av, char **env);

int		builtin_exit(int ac, char **av);
int		builtin_cd(char **av, char ***envp);
int		builtin_setenv(char **av, char ***env);
int		builtin_unsetenv(char **av, char ***env);
int		builtin_env(char **env);

#endif
