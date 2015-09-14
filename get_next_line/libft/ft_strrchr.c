/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 15:14:28 by anowak            #+#    #+#             */
/*   Updated: 2014/11/12 18:29:15 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char const *s, int c)
{
	int				x;
	unsigned char	*r;

	x = 0;
	r = (unsigned char *)s;
	while (r[x])
		x++;
	while (x)
	{
		if (r[x] == c)
			return ((char *)&r[x]);
		x--;
	}
	if (r[x] == c)
		return ((char *)&r[x]);
	return (NULL);
}
