/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_options_width.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/14 19:24:51 by anowak            #+#    #+#             */
/*   Updated: 2015/03/14 19:33:54 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		put_width(t_conv *c, int len)
{
	int ret;
	int width;

	ret = 0;
	width = c->width;
	while (width > len)
	{
		if ((c->zero && !c->minus && c->type != 'p')
			|| (c->type == 'p' && !c->precision && c->zero))
			write(1, "0", 1);
		else
			write(1, " ", 1);
		ret++;
		width--;
	}
	return (ret);
}

int		put_precision(t_conv *c, int len)
{
	int ret;

	ret = 0;
	if (c->precision)
	{
		while (c->precision > len)
		{
			write(1, "0", 1);
			ret++;
			c->precision--;
		}
	}
	return (ret);
}

int		width_num_process(t_conv *c, int len, int flagneg)
{
	int ret;

	ret = 0;
	if (c->precision > (flagneg ? len - 1 : len)
		&& c->precision > 0 && !c->minus)
		c->width = c->width - c->precision + (flagneg ? len - 1 : len);
	if (!flagneg && (c->space || c->plus))
	{
		if (c->zero && c->width > len)
		{
			len += space_plus(c);
			ret++;
		}
		else if (!c->minus && c->width && c->width > len)
			c->width--;
	}
	if (!c->minus)
		ret += put_width(c, len);
	if (flagneg && !c->zero)
		write(1, "-", 1);
	if (!flagneg && (c->space || c->plus))
		ret += space_plus(c);
	ret += put_precision(c, (flagneg ? len - 1 : len));
	return (ret);
}

int		width_num(t_conv *c, int len, int flagneg)
{
	int ret;

	ret = 0;
	if (c->width || c->precision)
	{
		if (flagneg && c->zero)
			write(1, "-", 1);
		if (*(long long*)c->arg == 0 && !c->minus && c->precision == -1)
			len--;
		ret = width_num_process(c, len, flagneg);
	}
	else if (flagneg)
		write(1, "-", 1);
	if (c->precision == -1 && *(long long*)c->arg == 0)
		ret--;
	return (ret);
}

int		width_str(t_conv *c, int len)
{
	int ret;

	ret = 0;
	if (c->width || c->precision)
	{
		if (c->precision == -1)
			c->width += len;
		else if (c->precision > 0 && len > c->precision)
			c->width = c->width - c->precision + len;
		ret += put_width(c, len);
		if (c->precision < len)
			ret += put_precision(c, len);
	}
	return (ret);
}
