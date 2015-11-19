/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/12 19:12:34 by anowak            #+#    #+#             */
/*   Updated: 2015/11/19 16:41:29 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strinsert(char *str, char c, int n)
{
	char *new;
	char *end;

	new = NULL;
	if (str)
		if (n <= (int)ft_strlen(str))
		{
			end = ft_strdup(str + n);
			if (!(new = ft_strnew(ft_strlen(str) + 1)))
				return (NULL);
			ft_strncpy(new, str, n);
			new[n] = c;
			if (end)
				ft_strcat(new, end);
			free(end);
			return (new);
		}
	return (ft_strndup(&c, 1));
}
