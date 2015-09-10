/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/16 18:14:26 by anowak            #+#    #+#             */
/*   Updated: 2015/07/16 18:24:19 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	builtin_exit(int ac, char **av)
{
	if (ac < 2)
	{
		exit(0);
	}
	if (ac == 2)
	{
		if (ft_atoi(av[1]))
			exit(ft_atoi(av[1]));
		else
			ft_putendl_fd("Error : argument is not a number", 2);
	}
	else
		ft_putendl_fd("Error : too many arguments to builtin", 2);
	return (1);
}
