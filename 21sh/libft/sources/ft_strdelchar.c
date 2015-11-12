/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdelchar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/12 18:45:42 by anowak            #+#    #+#             */
/*   Updated: 2015/11/12 19:12:27 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strdelchar(char *str, int n)
{
	char *new;
	char *end;

	new = NULL;
	if (str)
		if (n < (int)ft_strlen(str))
		{
			if (!(new = ft_strnew(ft_strlen(str))))
				return (NULL);
			end = ft_strdup(str + n + 1);
			ft_strncpy(new, str, n);
			ft_strcat(new, end);
			free(end);
			free(str);
		}
	return (new);
}
