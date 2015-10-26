/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/02 17:04:28 by anowak            #+#    #+#             */
/*   Updated: 2014/09/02 20:22:52 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_putnbr(int n);

int		ft_recursive_factorial(int nb)
{
	int f;

	if ((nb < 0) || (nb > 12))
		return (0);
	if (nb > 1)
		f = nb * ft_recursive_factorial((nb - 1));
	else
		return (1);
	return (f);
}
