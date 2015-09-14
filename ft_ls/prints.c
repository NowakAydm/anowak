/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/07 20:21:08 by anowak            #+#    #+#             */
/*   Updated: 2015/01/07 20:21:09 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_error(char *name)
{
	if (name)
	{
		ft_putstr_fd("ft_ls: ", 2);
		perror(name);
		errno = 0;
	}
	else
	{
		errno = ENOMEM;
		perror("ft_ls");
		exit(0);
	}
}

void	print_dir_name(t_dir *dir)
{
	if (!(dir->name))
	{
		if ((dir->tab[0]))
			(dir->ls)->first_dir = 1;
		return ;
	}
	if (((dir->ls)->dir_name)->left
		|| ((dir->ls)->dir_name)->right
		|| (dir->ls)->files
		|| (dir->is_rr))
	{
		if ((dir->ls)->first_dir)
			ft_putchar('\n');
		else
			(dir->ls)->first_dir = 1;
		ft_putstr(dir->name);
		ft_putendl(":");
	}
}

void	print_total(t_dir *dir)
{
	int i;
	int x;

	i = 0;
	x = -1;
	while (++x < dir->filenum)
		if (!(check_hidden_file(dir->ls, dir->name, dir->tab[x][0])))
			i++;
	if (i != dir->filenum)
	{
		ft_putstr("total ");
		ft_putnbrendl(dir->total_blocks);
	}
}

void	print_rev_tab(t_dir *dir)
{
	while (dir->filenum)
		if (check_hidden_file(dir->ls, dir->name, dir->tab[--dir->filenum][0]))
		{
			if ((dir->ls)->l)
				print_list(dir->tab[dir->filenum], dir);
			else
			{
				ft_putstr(dir->tab[dir->filenum][0]);
				if ((dir->ls)->p && dir->tab[dir->filenum][1][0] == 'd')
					ft_putendl("/");
				else
					ft_putchar('\n');
			}
		}
}

void	print_tab(t_dir *dir)
{
	int	i;

	i = 0;
	(dir->ls)->first_dir = 1;
	if ((dir->ls)->l && dir->name)
		print_total(dir);
	if ((dir->ls)->r && !(dir->ls)->f)
		print_rev_tab(dir);
	else
	{
		while (i < dir->filenum)
			if (check_hidden_file(dir->ls, dir->name, dir->tab[i++][0]))
			{
				if ((dir->ls)->l)
					print_list(dir->tab[i - 1], dir);
				else
				{
					ft_putstr(dir->tab[i - 1][0]);
					if ((dir->ls)->p && dir->tab[i - 1][1][0] == 'd')
						ft_putendl("/");
					else
						ft_putchar('\n');
				}
			}
	}
}
