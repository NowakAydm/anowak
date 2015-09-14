/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_scan.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/25 03:05:22 by anowak            #+#    #+#             */
/*   Updated: 2015/03/14 19:00:22 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		get_arg(t_conv *c, t_pf *pf)
{
	if (ft_strchr("diouxXcp", c->type))
	{
		if (!(c->arg = (long long int*)ft_memalloc(sizeof(long long int))))
			return (-1);
		*((long long int*)c->arg) = va_arg(pf->ap, long long int);
	}
	else if (c->type == 's' && c->size != 'l')
	{
		c->arg = va_arg(pf->ap, char*);
		if (c->arg)
			if (!(c->arg = ft_strdup((char*)c->arg)))
				return (-1);
	}
	else if (c->type == 's' && c->size == 'l')
	{
		c->arg = va_arg(pf->ap, wchar_t*);
		if (c->arg)
			if (!(c->arg = ft_wstrdup((wchar_t*)c->arg)))
				return (-1);
	}
	return (0);
}

t_conv	*convert_type(t_conv *c)
{
	if (ft_strchr("DOUSC", c->type))
	{
		c->type = ft_tolower(c->type);
		c->size = 'l';
	}
	else if (c->type == 'p')
	{
		c->size = 'l';
		c->sharp = 1;
		if (c->precision && c->precision != -1)
			c->precision += 2;
	}
	else if (!(ft_strchr("sSpdDoOuUxXcCi", c->type)) && c->precision)
		c->precision = 0;
	if (c->type == 'c' && c->precision == -1)
		c->precision = 0;
	else if (c->precision && ft_strchr("diouixX", c->type) && c->zero)
		c->zero = 0;
	return (c);
}

int		add_conv(const char *restrict format, t_pf *pf)
{
	int		i;
	int		pos;
	t_conv	*new;
	t_list	*lst;

	i = 1;
	pos = -1;
	if (!(new = (t_conv *)ft_memalloc(sizeof(t_conv))))
		return (-1);
	while (!(new->type) && format[i] && pos != i)
	{
		pos = i;
		i += set_options((format + i), new);
		i += set_width((format + i), new, pf);
		i += set_precision((format + i), new, pf);
		i += set_size((format + i), new);
	}
	i += set_type((format + i), new);
	if (new->type)
		if (get_arg(convert_type(new), pf) == -1)
			return (-1);
	new->len = i;
	lst = ft_lstnew(new, sizeof(t_conv));
	ft_lstaddend(&(pf->list), lst);
	return (i);
}

int		scan_format(const char *restrict format, t_pf *pf)
{
	int	i;
	int	x;

	i = 0;
	if (format)
		while (format[i])
		{
			while (format[i] && format[i] != '%')
				i++;
			if (format[i] == '%')
			{
				x = 0;
				if ((x = add_conv((format + i), pf)) == -1)
					return (-1);
				else
					i += x;
			}
		}
	return (0);
}
