/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/03 16:14:30 by anowak            #+#    #+#             */
/*   Updated: 2015/10/30 19:11:56 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int		x;
	char				*str1;
	char				*str2;

	x = 0;
	if (s1 && s2)
	{
		str1 = (char *)s1;
		str2 = (char *)s2;
		while (str1[x] || str2[x])
		{
			if (str1[x] != str2[x])
			{
				if (str1[x] == 0 && str2[x] < 0)
					return (str2[x]);
				if (str2[x] == 0 && str1[x] < 0)
					return (-str1[x]);
				else
					return (str1[x] - str2[x]);
			}
			x++;
		}
		return (0);
	}
	return (-1);
}
