/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 15:36:09 by anowak            #+#    #+#             */
/*   Updated: 2014/11/12 12:12:47 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char const *src, size_t n)
{
	size_t ldst;
	size_t lsrc;

	ldst = ft_strlen(dst);
	lsrc = ft_strlen(src);
	if (ldst >= n)
		return (lsrc + n);
	else
		ft_strncat(dst, src, n - ldst - 1);
	return (ldst + lsrc);
}
