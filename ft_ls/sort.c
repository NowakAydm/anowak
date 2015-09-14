/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/07 20:21:21 by anowak            #+#    #+#             */
/*   Updated: 2015/01/07 20:21:21 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	sort_av(char **av, int n)
{
	int		change;
	int		i;
	char	*tmp;

	change = 1;
	while (change == 1)
	{
		change = 0;
		i = 2;
		while (i < n)
		{
			if (av[i][0] && ft_strcmp(av[i], av[i - 1]) < 0)
			{
				tmp = av[i];
				av[i] = av[i - 1];
				av[i - 1] = tmp;
				change = 1;
			}
			i++;
		}
	}
}

int		partition_name(char ***tab, int c, int start, int end)
{
	int left;
	int	right;

	left = start;
	right = end;
	while (left < right)
	{
		while (ft_strcmp(tab[left][c], tab[start][c]) <= 0 && left < end)
			left++;
		while (ft_strcmp(tab[right][c], tab[start][c]) > 0)
			right--;
		if (left < right)
			swap_ptr(tab, left, right);
	}
	swap_ptr(tab, start, right);
	return (right);
}

int		partition_num(char ***tab, int c, int start, int end)
{
	int left;
	int	right;

	left = start;
	right = end;
	while (left < right)
	{
		while (ft_atod(tab[left][c]) - ft_atod(tab[start][c]) >= 0
				&& left < end)
			left++;
		while (ft_atod(tab[right][c]) - ft_atod(tab[start][c]) < 0)
			right--;
		if (left < right)
			swap_ptr(tab, left, right);
	}
	swap_ptr(tab, start, right);
	return (right);
}

void	resort_tab(t_dir *dir, int start, int end, int c)
{
	int x;

	while ((x = start) < end)
	{
		if (ft_atod(dir->tab[x][c]) == ft_atod(dir->tab[start][c]))
			while (x < end
				&& ft_atod(dir->tab[x + 1][c]) == ft_atod(dir->tab[start][c]))
				x++;
		if (x > start)
			sort_tab(dir, start, x, 14 * end);
		start = x + 1;
	}
}

char	***sort_tab(t_dir *dir, int start, int end, int flag)
{
	int pivot;
	int c;

	c = 0;
	if ((dir->ls)->t && flag < 4 * end)
		c = 6;
	if ((dir->ls)->ss && flag < 4 * end)
		c = 5;
	if (end > start)
	{
		if (c != 0)
			pivot = partition_num(dir->tab, c, start, end);
		else
			pivot = partition_name(dir->tab, c, start, end);
		sort_tab(dir, start, pivot - 1, flag + 1);
		sort_tab(dir, pivot + 1, end, flag + 1);
	}
	if (flag == 1 && ((dir->ls)->t || (dir->ls)->ss))
		resort_tab(dir, start, end, c);
	return (dir->tab);
}
