/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/21 04:35:55 by anowak            #+#    #+#             */
/*   Updated: 2015/05/04 19:28:53 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_ltoa_base(long long n, long long base)
{
	char	*str;
	char	*ret;
	int		x;

	x = 0;
	if (!(str = (char *)ft_memalloc(sizeof(char) * 100)))
		return (NULL);
	while (n / base)
	{
		if (base > 10 && ft_abs(n % base) > 9)
			str[x] = ft_abs(n % base) - 10 + 'a';
		else
			str[x] = ft_abs(n % base) + '0';
		n = n / base;
		x++;
	}
	if (base > 10 && ft_abs(n % base) > 9)
		str[x] = ft_abs(n % base) - 10 + 'a';
	else
		str[x] = ft_abs(n % base) + '0';
	if (n < 0 && base == 10)
		str[++x] = '-';
	ret = ft_strndup(str, x + 2);
	free(str);
	return (ft_strrev(ret));
}
