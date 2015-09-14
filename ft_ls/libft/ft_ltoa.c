/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/15 01:46:56 by anowak            #+#    #+#             */
/*   Updated: 2015/03/16 04:29:25 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_ltoa(long long n)
{
	char	*str;
	int		x;

	x = 0;
	ft_putstr(NULL);
	str = (char*)ft_memalloc((n >= 0 ? ft_nbrlen(n) + 1 : ft_nbrlen(n) + 2));
	if (!str)
		return (NULL);
	while (n / 10)
	{
		str[x] = ft_abs(n % 10) + '0';
		n /= 10;
		x++;
	}
	str[x] = ft_abs(n % 10) + '0';
	if (n < 0)
		str[x + 1] = '-';
	return (ft_strrev(str));
}
