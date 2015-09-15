/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/14 20:13:16 by anowak            #+#    #+#             */
/*   Updated: 2015/09/15 11:22:55 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int		argument_is_in_quotes(char *line, t_list **list, int x)
{
	char	*str;
	int		y;

	y = 0;
	if (!(y = dist_to_next_quote(line + x, line[x - 1])))
		return (0);
	else if (y++)
	{
		if (!(str = ft_strndup(line + x, y - 1)))
			return (0);
		ft_lstaddend(list, ft_lstnew(str, ft_strlen(str) + 1));
		free(str);
	}
// TODO: corriger le comportement pour "ls ''-a" et "ls '' -a"
	return (x + y);
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
	while (line[x + y] && !(ft_isspace(line[x + y]))
		   && !(ft_isquote(line[x + y]))
		   && line[x + y] != '|'
		   && line[x + y] != ';')
		if (line[x + y++] == '\\')
			y++;
	if (y)
	{
		if (!(str = ft_strndup((line + x), y)))
			return (0);
		ft_lstaddend(list, ft_lstnew(str, ft_strlen(str) + 1));
		free(str);
	}
	return (x + y);
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
			x = argument_is_in_quotes(line, &list, ++x);
		else if (line[x])
			x = argument_not_in_quotes(line, &list, x);
		if (!x)
			return (NULL);
	}
	replace_by_env_var(list, *env, ret);
	return (list);
}
