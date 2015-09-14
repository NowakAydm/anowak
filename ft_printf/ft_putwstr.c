/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/25 06:55:31 by anowak            #+#    #+#             */
/*   Updated: 2015/03/16 04:05:09 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_putwstr(const wchar_t *s)
{
	int a;
	int ret;

	a = 1;
	ret = 0;
	if (s)
	{
		while (*s)
		{
			if ((a = ft_putwchar(s)) == -1)
				return (-1);
			s++;
			ret += a;
		}
	}
	return (ret);
}
