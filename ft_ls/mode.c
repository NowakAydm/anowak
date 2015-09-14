/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/07 17:54:56 by anowak            #+#    #+#             */
/*   Updated: 2015/03/16 03:29:17 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_illegal_option(char av)
{
	ft_putstr_fd("ft_ls: illegal option -- ", 2);
	ft_putchar_fd(av, 2);
	ft_putendl_fd("\nusage: ft_ls [-ARSTUacdfglprtu1] [file ...]", 2);
	exit(0);
}

int		set_ls_print_modes(t_lsmode *ls, char *av)
{
	if (*av == '1')
	{
		ls->one = 1;
		ls->l = 0;
	}
	else if (*av == 'l')
	{
		ls->l = 1;
		ls->one = 0;
	}
	else if (*av == 'a')
		ls->a = 1;
	else if (*av == 'A')
		ls->aa = 1;
	else if (*av == 'R')
		ls->rr = 1;
	else if (*av == 'd')
		ls->d = 1;
	else
		return (0);
	return (1);
}

int		set_ls_time_modes(t_lsmode *ls, char *av)
{
	if (*av == 'c')
	{
		ls->c = 1;
		ls->u = 0;
		ls->uu = 0;
	}
	else if (*av == 'u')
	{
		ls->c = 0;
		ls->u = 1;
		ls->uu = 0;
	}
	else if (*av == 'U')
	{
		ls->c = 0;
		ls->u = 0;
		ls->uu = 1;
	}
	else
		return (0);
	return (1);
}

int		set_ls_other_modes(t_lsmode *ls, char *av)
{
	if (*av == 'g')
	{
		ls->l = 1;
		ls->g = 1;
	}
	else if (*av == 'f')
	{
		ls->a = 1;
		ls->f = 1;
	}
	else
		return (0);
	return (1);
}

int		set_ls_mode(t_lsmode *ls, char *av)
{
	av++;
	while (*av)
	{
		if (set_ls_time_modes(ls, av) == 0)
			if (set_ls_print_modes(ls, av) == 0)
				if (set_ls_other_modes(ls, av) == 0)
				{
					if (*av == 'S')
						ls->ss = 1;
					else if (*av == 't')
						ls->t = 1;
					else if (*av == 'T')
						ls->tt = 1;
					else if (*av == 'r')
						ls->r = 1;
					else if (*av == 'p')
						ls->p = 1;
					else
						print_illegal_option(*av);
				}
		av++;
	}
	return (0);
}
