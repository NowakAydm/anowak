/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hidenp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/12 18:24:43 by exam              #+#    #+#             */
/*   Updated: 2014/09/12 18:32:14 by exam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write (1, &c, 1);
}

int		main(int argc, char **argv)
{
	int x;
	int y;

	x = 0;
	y = 0;
	if (argc == 3)
	{
		while (argv[2][x] != '\0')
		{
			if (argv[1][y] == argv[2][x])
				y++;
			if (argv[1][y] == '\0')
			{
				ft_putchar('1');
				ft_putchar('\n');
				return (0);
			}
			x++;
		}
		ft_putchar('0');
	}
	ft_putchar('\n');
	return (0);
}
