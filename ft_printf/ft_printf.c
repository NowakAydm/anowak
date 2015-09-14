/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/25 02:52:02 by anowak            #+#    #+#             */
/*   Updated: 2015/03/16 19:30:03 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		ft_printf(const char *restrict format, ...)
{
	static t_pf		*pf;

	if (!pf)
		if (!(pf = (t_pf *)ft_memalloc(sizeof(t_pf))))
			return (-1);
	if (pf->ret != -1)
		pf->ret = 0;
	if (format)
	{
		pf->ret = 0;
		va_start(pf->ap, format);
		if (scan_format(format, pf) == -1)
		{
			va_end(pf->ap);
			return (-1);
		}
		if (print_format(format, pf) == -1)
		{
			va_end(pf->ap);
			return (-1);
		}
		ft_lstdel(&pf->list, ft_lstdelcontent);
		va_end(pf->ap);
	}
	return (pf->ret);
}
