/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_prints_nbr.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/14 20:16:10 by anowak            #+#    #+#             */
/*   Updated: 2015/03/14 20:17:05 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*convert_uint(t_conv *c, int base)
{
	if (c->size == 'l')
		return (ft_ultoa_base((*(unsigned long*)c->arg), base));
	else if (c->size == 'L')
		return (ft_ultoa_base((*(unsigned long long*)c->arg), base));
	else if (c->size == 'h')
		return (ft_ultoa_base((*(unsigned short*)c->arg), base));
	else if (c->size == 'H')
		return (ft_ultoa_base((*(unsigned char*)c->arg), base));
	else if (c->size == 'j')
		return (ft_ultoa_base((*(uintmax_t*)c->arg), base));
	else if (c->size == 'z')
		return (ft_ultoa_base((*(size_t*)c->arg), base));
	else
		return (ft_ultoa_base((*(unsigned int*)c->arg), base));
}

char	*convert_int(t_conv *c, int base)
{
	if (c->size == 'l')
		return (ft_ltoa_base((*(long*)c->arg), base));
	else if (c->size == 'L')
		return (ft_ltoa_base((*(long long*)c->arg), base));
	else if (c->size == 'h')
		return (ft_ltoa_base((*(short*)c->arg), base));
	else if (c->size == 'H')
		return (ft_ltoa_base((*(char*)c->arg), base));
	else if (c->size == 'j')
		return (ft_ltoa_base((*(intmax_t*)c->arg), base));
	else if (c->size == 'z')
		return (ft_ltoa_base((*(size_t*)c->arg), base));
	else
		return (ft_ltoa_base((*(int*)c->arg), base));
}

int		print_int_process(t_conv *c, int len, char *str, int x)
{
	if (*str != '-' && (c->space || c->plus) && !c->precision && !c->width)
		len += space_plus(c);
	len += width_num(c, len, (*str == '-'));
	if (*(long long*)c->arg == 0 && !c->minus)
		len--;
	if (c->type == 'X')
		while (str[x++])
			str[x - 1] = ft_toupper(str[x - 1]);
	if (*str == '-')
		write(1, str + 1, ft_strlen(str + 1));
	else if ((c->precision >= 0)
				|| (*(long long*)c->arg != 0 && c->precision == -1))
		write(1, str, ft_strlen(str));
	else if (c->type == 'p')
		write(1, "0x", 2);
	if (c->minus && !(c->zero = 0))
		len += put_width(c, len);
	if (*(long long*)c->arg == 0 && !c->minus)
		len++;
	return (len);
}

int		print_int(t_conv *c)
{
	char	*str;
	int		base;
	int		len;
	int		x;

	x = 0;
	len = 0;
	base = 10;
	if (c->type == 'x' || c->type == 'X' || c->type == 'p')
		base = 16;
	if (c->type == 'o')
		base = 8;
	if (c->type != 'd' && c->type != 'i')
		str = convert_uint(c, base);
	else
		str = convert_int(c, base);
	if (!str)
		return (-1);
	c->str = &str;
	len = ft_strlen(str);
	if (c->sharp)
		len += sharp(c, len);
	len = print_int_process(c, len, str, x);
	free(str);
	return (len);
}
