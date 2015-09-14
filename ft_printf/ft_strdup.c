/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 13:32:07 by anowak            #+#    #+#             */
/*   Updated: 2015/01/25 06:41:18 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*ft_strdup(char const *s1)
{
	int		len;
	char	*s2;

	len = ft_strlen(s1);
	s2 = (char *)ft_memalloc((sizeof(char *) * len + 1));
	if (!s2)
		return (0);
	ft_memcpy(s2, s1, len);
	return (s2);
}
