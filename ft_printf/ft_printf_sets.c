/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_sets.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/18 05:10:02 by anowak            #+#    #+#             */
/*   Updated: 2015/03/14 20:33:38 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		set_options(const char *restrict format, t_conv *new)
{
	int i;

	i = 0;
	while (format[i] && ft_strchr("#0-+ ", format[i]))
	{
		if (format[i] == '#')
			new->sharp = 1;
		if (format[i] == '0')
			new->zero = 1;
		if (format[i] == '-')
			new->minus = 1;
		if (format[i] == '+')
		{
			new->plus = 1;
			new->space = 0;
		}
		if (format[i] == ' ' && !new->plus)
			new->space = 1;
		i++;
	}
	return (i);
}

int		set_width(const char *restrict format, t_conv *new, t_pf *pf)
{
	int	i;

	i = 0;
	if (*format)
	{
		if (*format == '*')
		{
			new->width = (int)va_arg(pf->ap, int);
			if (new->width < 0)
				new->minus = 1;
			new->width = ft_abs(new->width);
			i++;
		}
		else if (ft_isdigit(*format))
		{
			new->width = ft_atoi_neg(format);
			new->width = -new->width;
			while (ft_isdigit(*(format + i)))
				i++;
		}
	}
	return (i);
}

int		set_long_size(const char *restrict format, t_conv *new)
{
	if (*format == 'h' && *(format + 1) == 'h')
	{
		if (!(new->size))
			new->size = 'H';
		return (2);
	}
	else if (*format == 'l' && *(format + 1) == 'l')
	{
		new->size = 'L';
		return (2);
	}
	else
		return (0);
}

int		set_size(const char *restrict format, t_conv *new)
{
	int		ret;

	ret = 0;
	if (*format)
	{
		if (*(format + 1))
			ret = set_long_size(format, new);
		if (ret == 2)
			return (ret);
		if (ft_strchr("hljz", *format))
		{
			if (*format == 'h' && !(new->size))
				new->size = 'h';
			else if (*format == 'l' || *format == 'j' || *format == 'z')
				new->size = *format;
			return (1);
		}
	}
	return (0);
}

int		set_type(const char *restrict format, t_conv *new)
{
	if (*format)
	{
		new->type = *format;
		return (1);
	}
	return (0);
}
