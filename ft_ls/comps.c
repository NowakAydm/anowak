/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/07 18:14:55 by anowak            #+#    #+#             */
/*   Updated: 2015/01/12 01:21:32 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	free_tab(t_dir *dir)
{
	int x;
	int y;

	x = 0;
	while (x < dir->filenum)
	{
		y = 0;
		while (y < 7)
		{
			free(dir->tab[x][y]);
			y++;
		}
		free(dir->tab[x]);
		x++;
	}
	free(dir->tab);
	free(dir->l);
	free(dir);
	dir = NULL;
}

void	swap_ptr(char ***tab, int a, int b)
{
	char **tmp;

	tmp = tab[a];
	tab[a] = tab[b];
	tab[b] = tmp;
}

int		dir_name_comp(void *a, void *b)
{
	return (ft_strcmp(((t_dir*)a)->name, ((t_dir*)b)->name));
}

int		name_comp(void *a, void *b)
{
	return (ft_strcmp(a, b));
}

int		dir_date_comp(void *a, void *b)
{
	return (((t_dir*)b)->modif_date - ((t_dir*)a)->modif_date);
}
