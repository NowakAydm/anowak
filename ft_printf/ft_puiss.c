/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puiss.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/25 07:41:58 by anowak            #+#    #+#             */
/*   Updated: 2015/01/25 07:42:41 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

double	ft_puiss(int n, int puiss)
{
	if (puiss == 0)
		return (1);
	if (puiss == 1)
		return (n);
	else
		return (n * ft_puiss(n, puiss - 1));
}
