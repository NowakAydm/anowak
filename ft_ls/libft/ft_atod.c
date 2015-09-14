/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/15 01:49:28 by anowak            #+#    #+#             */
/*   Updated: 2014/12/15 01:49:34 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atod(const char *str)
{
	double	res;
	int		n;

	n = 0;
	res = 0;
	while (ft_isspace(*str))
		str++;
	if ((*str == '+' || *str == '-') && !ft_isdigit(*(str + 1)))
		return (0);
	if (*str == '+' || *str == '-')
		str++;
	while (ft_isdigit(*str) && ft_isdigit(*(str + 1)))
		str++;
	while (ft_isdigit(*str))
	{
		if (*str-- != '0')
			res -= (*(str + 1) - '0') * ft_puiss10(n);
		n++;
	}
	if (*str != '-' && res != 0)
		res = -res;
	return (res);
}
