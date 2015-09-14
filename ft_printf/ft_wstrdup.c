/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/25 06:51:10 by anowak            #+#    #+#             */
/*   Updated: 2015/03/14 20:23:01 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

wchar_t	*ft_wstrdup(wchar_t const *s1)
{
	int		x;
	wchar_t	*s2;

	x = 0;
	while (s1[x])
		x++;
	s2 = (wchar_t *)ft_memalloc((sizeof(wchar_t) * (x + 1)));
	if (!s2)
		return (0);
	ft_memcpy(s2, s1, sizeof(wchar_t) * x);
	return (s2);
}
