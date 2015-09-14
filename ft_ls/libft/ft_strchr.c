/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 15:09:33 by anowak            #+#    #+#             */
/*   Updated: 2014/11/12 18:28:21 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char *r;

	r = (unsigned char *)s;
	while (*r)
	{
		if (*r == c)
			return ((char *)r);
		r++;
	}
	if (c == 0)
		return ((char *)r);
	else
		return (NULL);
}
