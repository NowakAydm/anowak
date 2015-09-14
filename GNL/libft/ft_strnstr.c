/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 16:09:49 by anowak            #+#    #+#             */
/*   Updated: 2014/11/12 18:28:51 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	unsigned int	x;
	unsigned int	i;
	char			*str1;
	char			*str2;

	x = 0;
	str1 = (char *)s1;
	str2 = (char *)s2;
	if (!str2[x])
		return (str1);
	while (str1[x])
	{
		i = 0;
		while ((x + i) < n && str1[x + i] == str2[i] && str2[i])
			i++;
		if (n != 0 && !str2[i])
			return (&str1[x]);
		x++;
	}
	return (NULL);
}
