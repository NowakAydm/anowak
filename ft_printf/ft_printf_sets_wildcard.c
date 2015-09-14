/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_sets_wildcard.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/14 19:08:56 by anowak            #+#    #+#             */
/*   Updated: 2015/03/14 20:34:17 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		set_precision_wild(t_conv *new, t_pf *pf)
{
	int i;

	i = 1;
	new->precision = (int)va_arg(pf->ap, int);
	i++;
	if (new->precision < 0)
	{
		new->precision = 0;
		return (i);
	}
	if (!new->precision)
		new->precision = -1;
	return (i);
}

int		set_precision(const char *restrict format, t_conv *new, t_pf *pf)
{
	int i;

	i = 1;
	if (*format == '.')
	{
		if (*(format + i))
		{
			if (*(format + i) == '*')
				return (set_precision_wild(new, pf));
			else
			{
				if (*(format + i) == '-')
					return (1);
				new->precision = ft_atoi_neg(format + i);
				new->precision = -new->precision;
				while (ft_isdigit(*(format + i)))
					i++;
			}
			if (!new->precision)
				new->precision = -1;
		}
		return (i);
	}
	return (0);
}
