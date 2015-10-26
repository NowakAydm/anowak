/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/02 21:11:59 by anowak            #+#    #+#             */
/*   Updated: 2014/09/03 21:48:01 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void ft_putnbr(int x);
void ft_putchar(char c);

int ft_sqrt(int nb)
{
	int x;
	int min;
	int max;
	int n;

	min = 0;
	max = nb;
	n = 50;
	while (n > 0)
	{
		ft_putnbr(x);
		ft_putchar('\n');
		x = (max + min) / 2;
		if ((x * x) > nb)
			max = x;
		if ((x * x) < nb)
			min = x;
		if ((x * x) == nb)
			return (x);
		n--;
	}
	return (0);
}
