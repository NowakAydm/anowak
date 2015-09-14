/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/24 16:17:09 by anowak            #+#    #+#             */
/*   Updated: 2015/01/12 01:11:37 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <sys/dir.h>
# include <sys/acl.h>
# include "../libft/includes/libft.h"
# include "ft_ls_struct.h"

/*
**	Main
*/
t_dir	*new_dir(t_dir *dir);
void	process_dir(void *d);
void	add_file(t_lsmode *ls, char *av);
void	add_dir(t_lsmode *ls, char *av);

/*
**  Mode
*/
void	print_illegal_option(char av);
int		set_ls_print_modes(t_lsmode *ls, char *av);
int		set_ls_time_modes(t_lsmode *ls, char *av);
int		set_ls_mode(t_lsmode *ls, char *av);

/*
**  Sets
*/
void	fill_tab(t_dir *dir);
int		check_hidden_file(t_lsmode *ls, char *dir, char *s);
int		check_if_dir(char *name, t_lsmode *ls);
t_dir	*set_dir_name(char *name, t_lsmode *ls);
void	add_r_dir(t_dir *dir, char *full_path, char **tab);

/*
**	Prints
*/
void	print_error(char *name);
void	print_dir_name(t_dir *dir);
void	print_total(t_dir *dir);
void	print_rev_tab(t_dir *dit);
void	print_tab(t_dir *dit);

/*
**	Sort
*/
void	sort_av(char **av, int n);
int		partition_name(char ***tab, int c, int start, int end);
int		partition_num(char ***tab, int c, int start, int end);
char	***sort_tab(t_dir *dir, int start, int end, int flag);

/*
**	Comps
*/
void	free_tab(t_dir *dir);
void	swap_ptr(char ***tab, int a, int b);
int		dir_name_comp(void *a, void *b);
int		name_comp(void *a, void *b);
int		dir_date_comp(void *a, void *b);

/*
**	Printlist
*/
t_len	*get_len(char **tab);
void	put_spaces(int i, t_len *l, t_dir *dir);
void	print_size(char **tab, t_dir *dir, t_len *l);
int		print_date(char *time, t_lsmode *ls);
void	print_list(char **tab, t_dir *dir);

/*
**	Listdata
*/
char	*get_link(char *full_path);
char	file_type(t_stat *s, char *full_path);
char	*file_mode(t_stat *s, char *full_path);
char	*ext_attr(char *full_path, char *mode, char *link);
void	get_list_data(char **tab, char *full_path, t_stat *s, t_dir *dir);

/*
**	List
*/
char	*set_full_path(char *dirname, char *filename);
void	set_max_len(char **tab, t_dir *dir);
t_stat	*get_stat(char *full_path);
char	*get_time(t_dir *dir, t_stat *s);
char	**fill_list(char **tab, char *path, t_dir *dir);

#endif
