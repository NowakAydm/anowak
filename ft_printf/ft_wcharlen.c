/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcharlen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/15 21:35:02 by anowak            #+#    #+#             */
/*   Updated: 2015/03/16 19:23:45 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

size_t		ft_wcharlen(const wchar_t *s)
{
	int		n;
	char	*str;

	if (!(str = ft_ultoa_base((unsigned long)*s, 2)))
		return (0);
	n = ft_strlen(str);
	free(str);
	if (n <= 7)
		return (1);
	else if (n > 8 && n < 12)
		return (2);
	else if (n >= 12 && n < 17)
		return (3);
	else if (n >= 17)
		return (4);
	else
		return (0);
}
