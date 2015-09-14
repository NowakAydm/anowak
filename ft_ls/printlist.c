/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printlist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/07 20:20:58 by anowak            #+#    #+#             */
/*   Updated: 2015/04/20 17:17:30 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_len	*get_len(char **tab)
{
	t_len	*l;

	if (!(l = (t_len*)ft_memalloc(sizeof(t_len))))
		print_error(NULL);
	l->link_len = (int)ft_strlen(tab[2]);
	l->uid_len = (int)ft_strlen(tab[3]);
	l->gid_len = (int)ft_strlen(tab[4]);
	l->size_len = (int)ft_strlen(tab[5]);
	l->maj_len = (int)ft_strlen(tab[7]);
	l->min_len = (int)ft_strlen(tab[8]);
	return (l);
}

void	put_spaces(int i, t_len *l, t_dir *dir)
{
	if (i == 1)
		while (l->link_len++ - 1 < (dir->max)->link_len)
			ft_putchar(' ');
	if (i == 2)
		while (l->uid_len++ - 2 < (dir->max)->uid_len)
			ft_putchar(' ');
	if (i == 3)
		while (l->gid_len++ - 1 < (dir->max)->gid_len)
			ft_putchar(' ');
	if (i == 4)
		while (l->maj_len++ - 2 < (dir->max)->maj_len)
			ft_putchar(' ');
	if (i == 5)
		while (l->min_len++ - 1 < (dir->max)->min_len)
			ft_putchar(' ');
	if (i == 6)
		while (l->size_len++ - 1 < (dir->max)->size_len)
			ft_putchar(' ');
	if (i == 7)
		while (l->size_len++ - 4 < ((dir->max)->min_len + (dir->max)->maj_len))
			ft_putchar(' ');
}

void	print_size(char **tab, t_dir *dir, t_len *l)
{
	if (tab[1][0] == 'c' || tab[1][0] == 'b')
	{
		put_spaces(4, l, dir);
		ft_putstr(tab[7]);
		ft_putchar(',');
		put_spaces(5, l, dir);
		ft_putstr(tab[8]);
	}
	else
	{
		if (!(dir->special_file))
			put_spaces(6, l, dir);
		else
			put_spaces(7, l, dir);
		ft_putstr(tab[5]);
	}
	ft_putchar(' ');
}

int		print_date(char *t, t_lsmode *ls)
{
	char	*str;
	time_t	*mtime;

	mtime = (time_t*)ft_memalloc(sizeof(time_t));
	*mtime = ft_atod(t);
	if (ctime(mtime) == NULL)
		return (1);
	str = ctime(mtime) + 4;
	if (ls->tt)
		ft_strclr(str + 20);
	else
	{
		if (!((time(NULL) - *mtime) > -1
			&& (time(NULL) - *mtime) < (3600 * 24 * 365 / 2)))
		{
			str[7] = ' ';
			if (ft_isdigit(str[17]))
				ft_memcpy(str + 8, str + 16, 4);
			else
				ft_memcpy(str + 8, str + 20, 8);
		}
		ft_strclr((str[12] == ':' ? str + 12 : str + 13));
	}
	ft_putstr(str);
	return (0);
}

void	print_list(char **tab, t_dir *dir)
{
	dir->l = get_len(tab);
	ft_putstr(tab[1]);
	put_spaces(1, dir->l, dir);
	ft_putstr(tab[2]);
	ft_putchar(' ');
	if (!(dir->ls)->g)
	{
		ft_putstr(tab[3]);
		put_spaces(2, dir->l, dir);
	}
	ft_putstr(tab[4]);
	put_spaces(3, dir->l, dir);
	print_size(tab, dir, dir->l);
	while (print_date(tab[6], dir->ls) == 1)
		fill_list(tab, dir->name, dir);
	ft_putchar(' ');
	ft_putstr(tab[0]);
	if ((dir->ls)->p && tab[1][0] == 'd')
		ft_putchar('/');
	if (tab[1][0] == 'l')
	{
		ft_putstr(" -> ");
		ft_putstr(tab[9]);
	}
	ft_putchar('\n');
}
