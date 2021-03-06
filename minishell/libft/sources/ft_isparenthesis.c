/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isparenthesis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/26 17:11:15 by anowak            #+#    #+#             */
/*   Updated: 2015/10/26 17:14:43 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_isparenthesis(int c)
{
	if (c == '(' || c == ')')
		return (1);
	else if (c == '[' || c == ']')
		return (1);
	else if (c == '{' || c == '}')
		return (1);
	return (0);
}
