/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/12 19:12:34 by anowak            #+#    #+#             */
/*   Updated: 2015/11/12 20:08:00 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strinsert(char *str, char c, int n)
{
	char *new;
	char *cha;
	char *end;

	new = NULL;
	cha = ft_strnew(1);
	*cha = c;
	if (str)
		if (n <= (int)ft_strlen(str))
		{
			if (!(new = ft_strnew(ft_strlen(str + 1))))
				return (NULL);
			end = ft_strdup(str + n);
			ft_strncpy(new, str, n);
			ft_strcat(new, cha);
			ft_strcat(new, end);
			free(end);
			free(str);
			free(cha);
			return (new);
		}
	return (cha);
}
