/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/25 04:27:49 by anowak            #+#    #+#             */
/*   Updated: 2015/02/16 01:25:51 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*ft_ultoa_base(unsigned long long n, long long base)
{
	char	*str;
	char	*ret;
	int		x;

	x = 0;
	if (!(str = (char *)ft_memalloc(sizeof(char) * 100)))
		return (NULL);
	while ((unsigned long long)n / base)
	{
		if (base > 10 && ft_abs(n % base) > 9)
			str[x] = ft_abs(n % base) - 10 + 'a';
		else
			str[x] = ft_abs((unsigned long long)n % base) + '0';
		n = (unsigned long long)n / base;
		x++;
	}
	if (base > 10 && ft_abs(n % base) > 9)
		str[x] = ft_abs(n % base) - 10 + 'a';
	else
		str[x] = ft_abs((unsigned long long)n % base) + '0';
	ret = ft_strndup(str, x + 2);
	free(str);
	return (ft_strrev(ret));
}
