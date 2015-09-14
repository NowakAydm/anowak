/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/14 15:12:18 by anowak            #+#    #+#             */
/*   Updated: 2014/11/14 15:33:57 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strrev(char *s)
{
	int		i;
	int		j;
	char	tmp;

	if (s)
	{
		i = 0;
		j = ft_strlen(s) - 1;
		while (i < j)
		{
			tmp = s[i];
			s[i] = s[j];
			s[j] = tmp;
			i++;
			j--;
		}
	}
	return (s);
}
