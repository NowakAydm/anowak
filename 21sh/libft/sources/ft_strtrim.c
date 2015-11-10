/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 17:46:07 by anowak            #+#    #+#             */
/*   Updated: 2014/11/14 18:40:59 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		start;
	int		x;
	char	*str;

	if (!s)
		return (NULL);
	x = 0;
	str = (char *)s;
	while (ft_isspace(str[x]) && str[x])
		x++;
	start = x;
	while (str[x])
		x++;
	x--;
	while (ft_isspace(str[x]) && x)
		x--;
	if (start > x)
		str = ft_strnew(1);
	else
		str = ft_strsub(str, start, x - start + 1);
	return (str);
}
