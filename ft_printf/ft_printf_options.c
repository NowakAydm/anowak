/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_options.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/25 05:16:25 by anowak            #+#    #+#             */
/*   Updated: 2015/03/14 20:35:29 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	sharp_hexa(t_conv *c, int len, char *s)
{
	if (c->type == 'p' && c->precision > len + 2)
		len += 2;
	if (c->precision != -1 && ((!c->minus && c->zero) || c->width <= len + 2))
	{
		if (c->type == 'x' || c->type == 'p')
			write(1, "0x", 2);
		if (c->type == 'X')
			write(1, "0X", 2);
		if (c->precision > 0 && c->type != 'p')
			c->precision += 2;
	}
	else
	{
		ft_strncpy(s, "0x", 2);
		ft_strncpy(s + 2, *c->str, ft_strlen(*c->str) + 1);
		free(*c->str);
		*c->str = ft_strdup(s);
	}
}

void	sharp_octal(t_conv *c, char *s)
{
	if ((!c->minus && c->zero) || c->precision == -1)
		write(1, "0", 1);
	else
	{
		ft_strncpy(s, "0", 1);
		ft_strncpy(s + 1, *c->str, ft_strlen(*c->str) + 1);
		free(*c->str);
		*c->str = ft_strdup(s);
	}
}

int		sharp(t_conv *c, int len)
{
	char s[ft_strlen(*c->str) + 2];

	c->sharp = 0;
	if (c->type == 'x' || c->type == 'X' || c->type == 'p')
	{
		if ((*(long long*)c->arg != 0) || c->type == 'p')
		{
			sharp_hexa(c, len, s);
			return (2);
		}
	}
	else if (c->type == 'o')
		if (*(long long*)c->arg != 0 || c->precision)
		{
			sharp_octal(c, s);
			return (1);
		}
	return (0);
}

int		space_plus(t_conv *c)
{
	if ((c->plus || c->space) && ft_strchr("aAdeEfFgGi", c->type))
	{
		if (c->plus)
			write(1, "+", 1);
		else if (c->space)
			write(1, " ", 1);
		c->plus = 0;
		c->space = 0;
		return (1);
	}
	return (0);
}

int		convert_precision(t_conv *c, int len)
{
	int x;
	int y;

	x = 0;
	y = 0;
	if (c->precision > 0)
	{
		while (*(((wchar_t*)c->arg) + y) && x < c->precision)
		{
			if (x + ft_wcharlen(((wchar_t*)c->arg) + y) <= c->precision)
				x += ft_wcharlen((wchar_t*)c->arg + y);
			y++;
		}
		return (x);
	}
	return (len);
}
