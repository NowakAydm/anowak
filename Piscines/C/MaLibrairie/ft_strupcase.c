/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strupcase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/03 19:26:17 by anowak            #+#    #+#             */
/*   Updated: 2014/09/03 20:16:28 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char *ft_strupcase(char *str)
{
	int x;

	x = 0;
	while (str[x])
	{
		if ((str[x] >= 'a') && (str[x] <= 'z'))
			str[x] -= 32;
		x++;
	}
	return (str);
}