/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/07 17:27:09 by anowak            #+#    #+#             */
/*   Updated: 2015/01/07 19:57:32 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_STRUCT_H
# define FT_LS_STRUCT_H

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;

typedef struct	s_len
{
	int			link_len;
	int			uid_len;
	int			gid_len;
	int			size_len;
	int			maj_len;
	int			min_len;
}				t_len;

typedef struct	s_lsmode
{
	int			l;
	int			rr;
	int			a;
	int			aa;
	int			d;
	int			r;
	int			t;
	int			c;
	int			u;
	int			uu;
	int			f;
	int			g;
	int			p;
	int			ss;
	int			tt;
	int			one;
	int			first_dir;
	t_btree		*dir_name;
	void		*files;
}				t_lsmode;

typedef struct	s_dir
{
	size_t		total_blocks;
	t_len		*l;
	t_len		*max;
	int			special_file;
	char		*name;
	DIR			*dir;
	t_list		*lst_dirent;
	int			filenum;
	char		***tab;
	t_lsmode	*ls;
	t_btree		*rr_dir;
	int			is_rr;
	time_t		modif_date;
}				t_dir;

#endif
