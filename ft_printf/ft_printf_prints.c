/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_prints.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/18 05:12:49 by anowak            #+#    #+#             */
/*   Updated: 2015/03/16 19:40:36 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		print_other(t_conv *c)
{
	int ret;

	ret = 1;
	if (!c->minus && c->width)
		ret += width_str(c, 1);
	if (c->precision)
		while (c->precision--)
		{
			write(1, "0", 1);
			ret++;
		}
	write(1, &c->type, 1);
	if (c->minus && c->width && !(c->zero = 0))
		ret += width_str(c, 1);
	return (ret);
}

int		print_conv(t_conv *c)
{
	if (c->type == 'd' || c->type == 'i' || c->type == 'o' || c->type == 'u'
		|| c->type == 'x' || c->type == 'X' || c->type == 'p')
		return (print_int(c));
	else if (c->type == 's')
	{
		if (c->size == 'l')
			return (print_long_string(c));
		else
			return (print_string(c));
	}
	else if (c->type == 'c')
	{
		if (c->size == 'l')
			return (print_wide_char(c));
		else
			return (print_char(c));
	}
	else if (c->type)
		return (print_other(c));
	return (0);
}

int		print_next_conv(t_pf *pf)
{
	int		len;
	int		x;
	t_list	*cur;

	cur = pf->list;
	pf->list = (pf->list)->next;
	if (((t_conv*)cur->content)->type)
	{
		x = 0;
		if ((x = print_conv((t_conv*)cur->content)) == -1)
			return (-1);
		else
			pf->ret += x;
		free(((t_conv*)cur->content)->arg);
	}
	len = ((t_conv*)cur->content)->len;
	ft_lstdelone(&cur, ft_lstdelcontent);
	free(cur);
	return (len);
}

int		print_format(const char *restrict format, t_pf *pf)
{
	int a;
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (format[x + y])
	{
		y += x;
		x = 0;
		while (format[x + y] && format[x + y] != '%')
			x++;
		write(1, (format + y), x);
		pf->ret += x;
		if (format[x + y] == '%')
		{
			a = 0;
			if ((a = print_next_conv(pf)) == -1)
				return (-1);
			else
				x += a;
		}
	}
	return (0);
}
