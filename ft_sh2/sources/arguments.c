/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/14 20:13:16 by anowak            #+#    #+#             */
/*   Updated: 2015/10/09 18:07:26 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int		argument_is_in_quotes(char *line, t_list **list, int x)
{
	char	*str;
	int		y;
	int		z;

	z = 0;
	if (line[x] == '<' || line[x] == '>')
	{
		z++;
		if (line[x + z])
			if (line[x + z] == '<' || line[x + z] == '>')
				z++;
		while (ft_isspace(line[x + z]))
			z++;
	}

	if (!(y = dist_to_next_quote(line + x + z, line[x + z])))
		return (0);
	else if (y == 1)
	{
		ft_lstaddend(list, ft_lstnew(ft_strdup(""), 1));
		return (x + z + 2);
	}
	else
	{
		if (!(str = ft_strndup(line + x, y + z)))
			return (0);
		str = remove_char(str, line[x + z]);
		ft_lstaddend(list, ft_lstnew(str, ft_strlen(str) + 1));
		free(str);
		y++;
	}
	return (x + y + z);
}

int		argument_not_in_quotes(char *line, t_list **list, int x)
{
	char	*str;
	int		y;

	y = 0;
	if (line[x] == '\\' && line[x + 1])
	{
		x++;
		y++;
	}
	else if (line[x] == ';' || line[x] == '|')
	{
		ft_lstaddend(list, ft_lstnew(line + x, 1));
		x++;
	}
	else if (line[x] == '<' || line[x] == '>')
	{
		y++;
		if (line[x + y])
			if (line[x + y] == '<' || line[x + y] == '>')
				y++;
		while (ft_isspace(line[x + y]))
			y++;
	}
	if (ft_isquote(line[x + y]))
		return (argument_is_in_quotes(line, list, x));

	while (line[x + y] && !(ft_isspace(line[x + y]))
		   && !(ft_isquote(line[x + y]))
		   && !(ft_strchr("|;<>", line[x + y])))
		if (line[x + y++] == '\\')
			y++;
	if (y)
	{
		str = ft_strndup((line + x), y);
		if (!(str = remove_char(str, '\\')))
			return (0);
		ft_lstaddend(list, ft_lstnew(str, ft_strlen(str) + 1));
		free(str);
	}
	return (x + y);
}

char	*remove_char(char *str, char c)
{
	char	*new;
	char	*spot;

	if (ft_strchr(str, c))
	{
		new = ft_strdup(str);
		while ((spot = ft_strchr(new, c)))
		{
			*spot = '\0';
			ft_strcat(new, spot + 1);
			spot = NULL;
		}
		spot = ft_strdup(new);
		free(new);
		free(str);
		return (spot);
	}
	return (str);
}

void	replace_by_env_var(t_list *list, char **env, int ret)
{
	t_list	*tmp;
	char	*str;

	tmp = list;
	while (tmp)
	{
		if (!ft_strcmp(tmp->content, "$?"))
		{
			free(tmp->content);
			tmp->content = ft_itoa(ret);
		}
		else if (*(char *)(tmp->content) == '$')
		{
			if ((str = get_in_env(env, (tmp->content + 1))))
			{
				free(tmp->content);
				tmp->content = ft_strdup(str);
			}
		}
		tmp = tmp->next;
	}
}

t_list	*split_into_args(char *line, char ***env, int ret)
{
	t_list	*list;
	int		x;
	int		y;

	list = NULL;
	x = 0;
	while (line[x])
	{
		y = 0;
		while (ft_isspace(line[x]))
			x++;
		if (ft_isquote(line[x]))
			x = argument_is_in_quotes(line, &list, x);
		else if (line[x])
			x = argument_not_in_quotes(line, &list, x);
		if (!x)
			return (NULL);
	}
	replace_by_env_var(list, *env, ret);
	return (list);
}
