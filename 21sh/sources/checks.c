/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/29 16:24:26 by anowak            #+#    #+#             */
/*   Updated: 2015/10/29 17:40:05 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

int		check_permissions(char *path)
{
	t_stat *s;

	if (!(s = (t_stat*)ft_memalloc(sizeof(t_stat))))
		return (0);
	if (lstat(path, s))
		if (stat(path, s))
		{
			if (s)
				free(s);
			return (-1);
		}
	if (S_ISDIR(s->st_mode))
	{
		free(s);
		return (-2);
	}
	free(s);
	if (!(access(path, F_OK)))
	{
		if ((access(path, X_OK)))
			return (-2);
		return (1);
	}
	return (-1);
}

int		check_everything(char *line)
{
	if (!(check_quotes_in_line(line)))
		if (!(check_pipe(line)))
			if (!(check_parenthesis(line)))
				return (0);
	return (1);
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

int		check_parenthesis(char *line)
{
	int		x;
	int		ret;

	x = -1;
	while (line[++x])
	{
		if (line[x] == '(' || line[x] == '[' || line[x] == '{')
		{
			ret = line[x++];
			while (line[x] && line[x] != ft_toclosingparenthesis(ret))
				if (line[x++] == '\\')
					x++;
			if (!(line[x]))
				return (write(1, "> ", 2));
			else
				ret = 0;
		}
		else if (line[x] == '\\')
			if (!(line[++x]))
				return ((write(1, "> ", 2) ? 1 : 1));
	}
	return (ret);
}

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
