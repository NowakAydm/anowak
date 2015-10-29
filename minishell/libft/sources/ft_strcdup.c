/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/26 16:49:44 by anowak            #+#    #+#             */
/*   Updated: 2015/05/26 18:57:26 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcdup(char const *s1, char c)
{
	int	x;

	x = 0;
	while (s1[x] != c)
		x++;
	if (s1[x] == c)
		return (ft_strndup(s1, x));
	return (ft_strdup(s1));
}
