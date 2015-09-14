/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 17:04:36 by anowak            #+#    #+#             */
/*   Updated: 2014/11/14 17:37:14 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;

	if (s1 || s2)
	{
		if (!s1 && s2)
			str = ft_strdup(s2);
		else if (s1 && !s2)
			str = ft_strdup(s1);
		else
		{
			str = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + 1);
			if (!str)
				return (NULL);
			ft_strcpy(str, s1);
			str = ft_strcat(str, s2);
		}
		return (str);
	}
	return (NULL);
}
