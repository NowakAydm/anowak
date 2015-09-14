/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_neg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/02 09:31:06 by anowak            #+#    #+#             */
/*   Updated: 2015/02/02 09:32:27 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_atoi_neg(const char *str)
{
	int res;
	int n;

	n = -1;
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
		if ((n++ >= 9 && *str > 2 && res < -147483648 && *str != 0))
			return (0);
		if (*str-- != '0')
			res -= (*(str + 1) - '0') * ft_puiss10(n);
	}
	return (res);
}
