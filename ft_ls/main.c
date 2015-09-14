/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/07 20:20:44 by anowak            #+#    #+#             */
/*   Updated: 2015/01/11 23:46:28 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dir	*new_dir(t_dir *dir)
{
	t_list		*new;
	t_dirent	*tmp_dirent;

	if (!(dir->dir = opendir(dir->name)))
		return (0);
	while ((tmp_dirent = readdir(dir->dir)))
	{
		if (!(new = ft_lstnew(tmp_dirent, sizeof(t_dirent))))
			print_error(NULL);
		ft_lstaddend(&dir->lst_dirent, new);
		dir->filenum++;
	}
	if (errno)
		return (0);
	if (closedir(dir->dir))
		return (0);
	return (dir);
}

void	process_dir(void *d)
{
	t_dir	*dir;

	errno = 0;
	dir = (t_dir*)d;
	if (dir->name)
	{
		print_dir_name(dir);
		if (!(dir = new_dir(dir)))
		{
			print_error(((t_dir*)d)->name);
			return ;
		}
	}
	fill_tab(dir);
	if (!(dir->name))
		print_dir_name(dir);
	if (!((dir->ls)->f))
		sort_tab(dir, 0, dir->filenum - 1, 1);
	if (dir->tab[0])
		print_tab(dir);
	if (!((dir->ls)->r) && (dir->rr_dir))
		ft_btree_infix(dir->rr_dir, process_dir);
	else if (dir->rr_dir)
		ft_btree_rev_infix(dir->rr_dir, process_dir);
	free_tab(d);
}

void	add_file(t_lsmode *ls, char *av)
{
	t_dir		*dir;
	t_dirent	*tmp_dirent;
	t_list		*new;

	if (!ls->files)
	{
		dir = set_dir_name(NULL, ls);
		ls->files = dir;
	}
	if (!(tmp_dirent = (t_dirent*)ft_memalloc(sizeof(t_dirent))))
		print_error(NULL);
	ft_memcpy(tmp_dirent->d_name, av, ft_strlen(av));
	if (!(new = ft_lstnew(tmp_dirent, sizeof(t_dirent))))
		print_error(NULL);
	ft_lstaddend(&((t_dir*)ls->files)->lst_dirent, new);
	((t_dir*)ls->files)->filenum++;
}

void	add_dir(t_lsmode *ls, char *av)
{
	t_dir		*dir;

	if (check_if_dir(av, ls))
	{
		dir = set_dir_name(av, ls);
		if (ls->t)
			ft_btree_insert(&ls->dir_name, dir, dir_date_comp);
		else if (ls->f)
			ft_btree_insert(&ls->dir_name, dir, 0);
		else
			ft_btree_insert(&ls->dir_name, dir, dir_name_comp);
		return ;
	}
	add_file(ls, av);
}

int		main(int ac, char **av)
{
	int			i;
	t_lsmode	*ls;

	i = 1;
	if (!(ls = (t_lsmode*)ft_memalloc(sizeof(*ls))))
		print_error(NULL);
	while (i < ac && av[i][0] == '-' && av[i][1])
		if (ft_strcmp(av[i++], "--") == 0)
			break ;
		else
			set_ls_mode(ls, av[i - 1]);
	if (!(ls->f))
		sort_av(av, ac - i - 1);
	if (i < ac)
		while (i < ac)
			add_dir(ls, av[i++]);
	else
		add_dir(ls, ".");
	if (ls->files)
		process_dir(ls->files);
	if (!ls->r)
		ft_btree_infix(ls->dir_name, process_dir);
	else
		ft_btree_rev_infix(ls->dir_name, process_dir);
	return (0);
}
