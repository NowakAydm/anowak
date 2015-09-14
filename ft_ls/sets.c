/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sets.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/07 20:21:15 by anowak            #+#    #+#             */
/*   Updated: 2015/01/07 20:21:15 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	fill_tab(t_dir *dir)
{
	t_list	*cur;
	int		i;

	i = 0;
	if (!(dir->tab = (char***)ft_memalloc(sizeof(char**) * dir->filenum + 1)))
		print_error(NULL);
	cur = dir->lst_dirent;
	while (cur && i < dir->filenum + 1)
	{
		if (!(dir->tab[i] = (char**)ft_memalloc(sizeof(char*) * 11)))
			print_error(NULL);
		if (!(dir->tab[i][0] = ft_strdup(((t_dirent*)cur->content)->d_name)))
			print_error(NULL);
		if ((dir->tab[i] = fill_list(dir->tab[i], dir->name, dir)))
			i++;
		else
		{
			free(dir->tab[i]);
			dir->filenum--;
		}
		cur = cur->next;
	}
	ft_lstdel(&dir->lst_dirent, ft_lstdelcontent);
}

int		check_hidden_file(t_lsmode *ls, char *dir, char *s)
{
	if (!dir)
		return (1);
	if (s[0] == '.')
	{
		if (ls->a)
			return (1);
		else if (ls->aa)
		{
			if (!ft_strcmp(s, ".") || !ft_strcmp(s, ".."))
				return (0);
		}
		else
			return (0);
	}
	return (1);
}

int		check_if_dir(char *name, t_lsmode *ls)
{
	t_stat	*s;

	if (ls->d)
		return (0);
	if (!(s = ft_memalloc(sizeof(t_stat))))
		print_error(NULL);
	if (!(ls->l))
		stat(name, s);
	else if ((lstat(name, s)))
		stat(name, s);
	if (S_ISDIR(s->st_mode))
	{
		free(s);
		return (1);
	}
	free(s);
	return (0);
}

t_dir	*set_dir_name(char *name, t_lsmode *ls)
{
	t_dir		*dir;

	if (!(dir = (t_dir*)ft_memalloc(sizeof(*dir))))
		print_error(NULL);
	if (name)
	{
		if (!(dir->name = ft_strdup(name)))
			print_error(NULL);
		dir->modif_date = get_stat(name)->st_mtime;
	}
	else
		dir->name = NULL;
	dir->ls = ls;
	return (dir);
}

void	add_r_dir(t_dir *dir, char *full_path, char **tab)
{
	t_dir	*r_dir;

	r_dir = set_dir_name(full_path, dir->ls);
	r_dir->is_rr = 1;
	r_dir->modif_date = ft_atod(tab[6]);
	if ((dir->ls)->t)
		ft_btree_insert(&dir->rr_dir, r_dir, dir_date_comp);
	else
		ft_btree_insert(&dir->rr_dir, r_dir, dir_name_comp);
}
