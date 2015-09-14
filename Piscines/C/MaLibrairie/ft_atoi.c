/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/04 19:34:58 by anowak            #+#    #+#             */
/*   Updated: 2014/09/08 14:12:57 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char*ft_atoi_where_to_start(char *str)
{
	int x;

	x = 0;
	while (str[x] == ' ')
		x++;
	if (((str[x] < 48) && (str[x] != 45)) || (str[x] > 57))
		return (0);
	if ((str[x] == 45) && ((str[x + 1] < 48) || (str[x + 1] > 57)))
		return (0);
	return (&str[x]);
}

int ft_puiss10(int y)
{
	int res;

	if (y > 1)
		res = 10 * (ft_puiss10(y - 1));
	if (y == 1)
		return (10);
	return (res);
}

int	ft_atoi(char *str)
{
	int x;
	int y;
	int res;

	x = 0;
	y = 0;
	res = 0;
	str = ft_atoi_where_to_start(str);
	if (str[x] == 45)
		x++;
	while ((str[x] > 47) && (str[x] < 58))
		x++;
	x--;
	res = str[x--] - 48;
	while ((str[x] > 47) && (str[x] < 58))
	{
		y++;
		if (str[x] != 48)
			res = res + ((str[x] - 48) * (ft_puiss10(y)));
		x--;
	}
	if (str[x] == 45)
		res *= -1;
	return (res);
}
