/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/14 19:42:06 by anowak            #+#    #+#             */
/*   Updated: 2015/09/15 11:05:03 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int		check_pipe(char *line)
{
	int		x;
	int		ret;
	char	*str;

	x = -1;
	ret = 0;
	str = NULL;
	if ((str = ft_strchr(line, '|')))
	{
		while (str[++x])
		{
			while (ft_isspace(str[x]))
				   x++;
			if ((ft_isquote(str[x]) && str[x] != str[x + 1])
				|| !(ft_strchr("'\"`;|><", str[x])))
				return (0);
		}
		if (!str[x])
			return (write(1, "pipe> ", 6));
	}
	return (ret);
}

int		prompt_missing_quote(int ret)
{
	if (ret == '"')
		write(1, "dquote> ", 9);
	else if (ret == '\'')
		write(1, "quote> ", 8);
	else if (ret == '`')
		write(1, "bquote> ", 9);
	return (ret);
}

int		check_quotes_in_line(char *line)
{
	int	x;
	int	ret;

	x = -1;
	ret = 0;
	while (line[++x])
	{
		if (line[x] == '\'' || line[x] == '"' || line[x] == '`')
		{
			ret = line[x++];
			while (line[x] && line[x] != ret)
				if (line[x++] == '\\')
					x++;
			if (!(line[x]))
				return (prompt_missing_quote(ret));
			else
				ret = 0;
		}
		else if (line[x] == '\\')
			if (!(line[++x]))
				return ((write(1, "> ", 2) ? 1 : 1));
	}
	return (ret);
}

int		dist_to_next_quote(char *line, int c)
{
	int y;

	y = 0;
	while (line[y] && line[y] != c)
		if (line[y++] == '\\')
			y++;
	if (!(line[y]))
	{
		ft_putendl_fd("Error : missing a quote", 2);
		return (0);
	}
	return (y);
}
