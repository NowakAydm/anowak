/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 13:32:07 by anowak            #+#    #+#             */
/*   Updated: 2014/11/06 18:42:33 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char const *s1)
{
	char	*s2;

	s2 = (char *)malloc((sizeof(char *) * ft_strlen(s1) + 1));
	if (!s2)
		return (0);
	ft_strcpy(s2, s1);
	return (s2);
}
