/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maff_alpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/12 18:19:43 by exam              #+#    #+#             */
/*   Updated: 2014/09/12 18:23:11 by exam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write (1, &c, 1);
}

int		main(void)
{
	int x;
	int y;

	x = 97;
	y = 66;
	while (x < 122)
	{
		ft_putchar(x);
		x += 2;
		ft_putchar(y);
		y += 2;
	}
	ft_putchar('\n');
	return (0);
}
