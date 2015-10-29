/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 15:34:27 by anowak            #+#    #+#             */
/*   Updated: 2014/11/12 18:29:34 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	unsigned int	x;
	unsigned int	n;
	char			*str1;
	char			*str2;

	x = 0;
	str1 = (char *)s1;
	str2 = (char *)s2;
	if (!str2[x])
		return (str1);
	while (str1[x])
	{
		n = 0;
		while (str1[x + n] == str2[n] && str1[x + n])
			n++;
		if (!str2[n])
			return (&str1[x]);
		x++;
	}
	return (NULL);
}
