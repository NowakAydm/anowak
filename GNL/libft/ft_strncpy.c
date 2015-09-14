/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 14:12:22 by anowak            #+#    #+#             */
/*   Updated: 2014/11/21 19:39:55 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, char const *src, size_t n)
{
	int x;

	x = 0;
	while (src[x] && n && dst)
	{
		dst[x] = src[x];
		x++;
		n--;
	}
	while (n && dst)
	{
		dst[x] = '\0';
		x++;
		n--;
	}
	return (dst);
}
