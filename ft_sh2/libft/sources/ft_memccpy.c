/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 21:28:54 by anowak            #+#    #+#             */
/*   Updated: 2014/11/07 22:13:59 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	char		*d;
	const char	*s;

	d = dst;
	s = src;
	while (n--)
	{
		if (*s == c)
		{
			*d++ = *s;
			return (d);
		}
		*d++ = *s++;
	}
	return (NULL);
}
