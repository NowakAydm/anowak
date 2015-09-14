/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 18:22:31 by anowak            #+#    #+#             */
/*   Updated: 2014/11/10 16:01:33 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
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
	if (*str != '-' && res != 0 && res > -2147483648)
		res = -res;
	else if (*str != '-' && res == -2147483648)
		return (0);
	return (res);
}
