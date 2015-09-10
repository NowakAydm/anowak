/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 16:18:54 by anowak            #+#    #+#             */
/*   Updated: 2014/11/14 18:45:43 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int		x;
	char				*str1;
	char				*str2;

	x = 0;
	str1 = (char *)s1;
	str2 = (char *)s2;
	while (s1 && s2 && (str1[x] || str2[x]) && x < n)
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
