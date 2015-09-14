/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/07 20:20:28 by anowak            #+#    #+#             */
/*   Updated: 2015/01/12 01:09:05 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*set_full_path(char *dirname, char *filename)
{
	char	*full_path;

	if (!(full_path = ft_strnew(ft_strlen(dirname) + ft_strlen(filename) + 1)))
		return (0);
	if (dirname)
	{
		if (ft_strrchr(dirname, '/') == (dirname + ft_strlen(dirname) - 1))
			ft_strclr(dirname + ft_strlen(dirname) - 1);
		full_path = ft_strcat(ft_strcpy(full_path, dirname), "/");
	}
	full_path = ft_strcat(full_path, filename);
	return (full_path);
}

void	set_max_len(char **tab, t_dir *dir)
{
	if (!dir->max)
		if (!(dir->max = (t_len*)ft_memalloc(sizeof(t_len))))
			print_error(NULL);
	if ((check_hidden_file(dir->ls, dir->name, tab[0])))
	{
		if ((int)ft_strlen(tab[2]) > (dir->max)->link_len)
			(dir->max)->link_len = ft_strlen(tab[2]);
		if ((int)ft_strlen(tab[3]) > (dir->max)->uid_len)
			(dir->max)->uid_len = ft_strlen(tab[3]);
		if ((int)ft_strlen(tab[4]) > (dir->max)->gid_len)
			(dir->max)->gid_len = ft_strlen(tab[4]);
		if ((int)ft_strlen(tab[5]) > (dir->max)->size_len)
			(dir->max)->size_len = ft_strlen(tab[5]);
		if ((int)ft_strlen(tab[7]) > (dir->max)->maj_len)
			(dir->max)->maj_len = ft_strlen(tab[7]);
		if ((int)ft_strlen(tab[8]) > (dir->max)->min_len)
			(dir->max)->min_len = ft_strlen(tab[8]);
	}
}

t_stat	*get_stat(char *full_path)
{
	t_stat	*s;

	if (!(s = (t_stat*)ft_memalloc(sizeof(t_stat))))
		print_error(NULL);
	if (lstat(full_path, s))
		if (stat(full_path, s))
			return (0);
	return (s);
}

char	*get_time(t_dir *dir, t_stat *s)
{
	if ((dir->ls)->c)
		return (ft_ltoa(s->st_ctime));
	if ((dir->ls)->u)
		return (ft_ltoa(s->st_atime));
	if ((dir->ls)->uu)
		return (ft_ltoa(s->st_birthtime));
	else
		return (ft_ltoa(s->st_mtime));
}

char	**fill_list(char **tab, char *path, t_dir *dir)
{
	t_stat	*s;
	char	*full_path;

	if (!(full_path = set_full_path(path, tab[0])))
		print_error(NULL);
	if (!(s = get_stat(full_path)))
	{
		print_error(tab[0]);
		return (0);
	}
	if (check_hidden_file(dir->ls, dir->name, tab[0]))
		dir->total_blocks += (size_t)s->st_blocks;
	get_list_data(tab, full_path, s, dir);
	tab[1] = ext_attr(full_path, tab[1], tab[9]);
	set_max_len(tab, dir);
	if ((dir->ls)->rr && !(dir->ls)->d && tab[1][0] == 'd'
		&& ft_strcmp(tab[0], ".") && ft_strcmp(tab[0], "..")
		&& check_hidden_file(dir->ls, dir->name, tab[0]))
		add_r_dir(dir, full_path, tab);
	free(full_path);
	return (tab);
}
