/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/25 06:51:27 by anowak            #+#    #+#             */
/*   Updated: 2015/03/14 20:23:23 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

size_t		ft_wstrlen(const wchar_t *s)
{
	size_t		i;

	i = 0;
	if (s)
		while (*s)
		{
			i += ft_wcharlen(s);
			s++;
		}
	return (i);
}