/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 18:30:40 by anowak            #+#    #+#             */
/*   Updated: 2014/11/15 17:28:08 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsplit(char const *s, char c)
{
	char	**tab;
	char	*str;
	int		i;
	int		x;

	i = 0;
	str = (char *)s;
	tab = (char **)malloc((sizeof(char *) * ft_count_words(str, c)) + 1);
	if (!tab || !s)
		return (NULL);
	while (*str)
	{
		x = 0;
		while (*str == c && *str)
			str++;
		if (!*str)
			break ;
		while (str[x] != c && str[x])
			x++;
		tab[i++] = ft_strndup(str, x);
		str = &str[x];
	}
	tab[i] = NULL;
	return (tab);
}
