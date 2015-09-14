/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_prints_txt.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/14 20:18:05 by anowak            #+#    #+#             */
/*   Updated: 2015/03/16 04:05:56 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		print_char(t_conv *c)
{
	int		w;
	char	b;

	w = 1;
	if (!c->minus)
		w += put_width(c, 1);
	b = *((char*)c->arg);
	write(1, &b, 1);
	if (c->minus && !(c->zero = 0))
		w += put_width(c, 1);
	return (w);
}

int		print_wide_char(t_conv *c)
{
	int w;

	w = 0;
	if (!c->minus)
		w += width_str(c, ft_wcharlen(((wchar_t*)c->arg)));
	w += ft_putwchar(((wchar_t*)c->arg));
	if (c->minus && !(c->zero = 0))
		w += width_str(c, ft_wcharlen(((wchar_t*)c->arg)));
	return (w);
}

int		print_string(t_conv *c)
{
	int len;
	int w;

	w = 0;
	if (!(c->arg) && !c->precision)
		return (write(1, "(null)", 6));
	len = ft_strlen(c->arg);
	if (!c->minus)
		w += width_str(c, len);
	if (c->precision)
		if (c->precision < len || c->precision == -1)
		{
			w += write(1, c->arg, c->precision);
			if (c->precision == -1)
				w++;
			if (c->minus)
				w += width_str(c, len + 1);
			return (w);
		}
	write(1, c->arg, len);
	if (c->minus && !(c->zero = 0))
		w += width_str(c, len);
	if (c->type == 'c')
		return (1 + w);
	return (len + w);
}

int		print_long_string_precision(t_conv *c, int len, int w)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (*(((wchar_t*)c->arg) + y) && x < c->precision)
	{
		if (x + ft_wcharlen(((wchar_t*)c->arg) + y) <= c->precision)
			x += ft_putwchar(((wchar_t*)c->arg + y));
		y++;
	}
	if (c->minus)
		w += width_str(c, len);
	return (x + w);
}

int		print_long_string(t_conv *c)
{
	int len;
	int w;

	w = 0;
	len = 0;
	if (!(c->arg) && !c->precision)
	{
		write(1, "(null)", 6);
		return (6);
	}
	if (c->type == 'c')
		return (ft_putwchar(((wchar_t*)c->arg)));
	len = ft_wstrlen(c->arg);
	len = convert_precision(c, len);
	if (!c->minus)
		w += width_str(c, len);
	if (c->precision)
		return (print_long_string_precision(c, len, w));
	len = ft_putwstr(c->arg);
	if (c->minus && !(c->zero = 0))
		w += width_str(c, len);
	return (len + w);
}
