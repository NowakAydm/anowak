/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/02 18:08:19 by anowak            #+#    #+#             */
/*   Updated: 2014/09/02 21:19:37 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int ft_iterative_power(int nb, int power)
{
	int i;
	int x;

	i = 1;
	x = nb;
	if ((power < 0) || (nb == 0))
		return (0);
	if (power == 0)
		return (1);
	while (i < power)
	{
		nb *= x;
		i++;
	}
	return (nb);
}
