/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/14 19:42:06 by anowak            #+#    #+#             */
/*   Updated: 2015/10/29 19:07:32 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int		argument_is_in_quotes(char *line, t_list **list, int x)
{
	char	*str;
	int		y;

	if (!(y = dist_to_next_quote(line + x, line[x])))
		return (0);
	else if (y == 1)
	{
		ft_lstaddend(list, ft_lstnew(ft_strdup(""), 1));
		return (x + 2);
	}
	else
	{
		if (!(str = ft_strndup(line + x, y + 1)))
			return (0);
		ft_lstaddend(list, ft_lstnew(str, ft_strlen(str) + 1));
		free(str);
		y++;
	}
	return (x + y);
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

int		dist_to_next_quote(char *line, int c)
{
	int y;

	y = 1;
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

int		find_path_to_command(t_cmd *new, char **path_dir)
{
	int	x;

	x = -1;
	if (!(new->path = ft_strnew(MAXPATHLEN)))
		return (0);
	if (new->argv[0][0] == '.' || new->argv[0][0] == '/')
	{
		ft_strcpy(new->path, new->argv[0]);
		return (check_permissions(new->path));
	}
	else if (path_dir)
	{
		while (path_dir[++x])
		{
			ft_strcpy(new->path, path_dir[x]);
			ft_strcat(new->path, "/");
			ft_strcat(new->path, new->argv[0]);
			if (check_permissions(new->path) != -1)
				return (check_permissions(new->path));
			ft_strclr(new->path);
		}
	}
	return (-1);
}
