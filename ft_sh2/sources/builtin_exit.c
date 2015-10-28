/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/16 18:14:26 by anowak            #+#    #+#             */
/*   Updated: 2015/10/28 14:56:25 by AdamNowak        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	builtin_exit(int ac, char **av)
{
	if (ac < 2)
	{
		ft_putendl("Exiting ft_minishell2 ... See you later .)");
		restore_term(NULL);
		exit(0);
	}
	if (ac == 2)
	{
		if (ft_atoi(av[1]))
		{
			restore_term(NULL);
			exit(ft_atoi(av[1]));
		}
		else
			ft_putendl_fd("Error : argument is not a number", 2);
	}
	else
		ft_putendl_fd("Error : too many arguments to builtin", 2);
	return (1);
}
