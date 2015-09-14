/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 18:45:33 by anowak            #+#    #+#             */
/*   Updated: 2014/11/21 19:39:47 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char const *s1, size_t n)
{
	char	*s2;

	if (!s1)
		return (NULL);
	s2 = ft_strnew(n);
	if (!s2)
		return (NULL);
	ft_strncpy(s2, s1, n);
	return (s2);
}
