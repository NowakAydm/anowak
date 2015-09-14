/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 20:16:54 by anowak            #+#    #+#             */
/*   Updated: 2015/01/18 03:07:08 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t x;

	x = 0;
	while (x < n)
	{
		*((char *)dst + x) = *((char *)src + x);
		x++;
	}
	return (dst);
}
