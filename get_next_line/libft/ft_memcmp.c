/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 15:24:21 by anowak            #+#    #+#             */
/*   Updated: 2014/11/08 15:32:40 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned int x;

	x = 0;
	while (x < n)
	{
		if (*((unsigned char *)s1 + x) != *((unsigned char *)s2 + x))
			return (*((unsigned char *)s1 + x) - *((unsigned char *)s2 + x));
		x++;
	}
	return (0);
}
