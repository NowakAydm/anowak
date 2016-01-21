/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/14 20:13:16 by anowak            #+#    #+#             */
/*   Updated: 2016/01/21 18:19:46 by AdamNowak        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int		add_argument_to_list(char *line, t_list **list, int x, int y)
{
	char	*str;

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

int		argument_not_in_quotes(char *line, t_list **list, int x)
{
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
	else if (arg_is_fd_redirector(line + x))
		y += 4;
	return (add_argument_to_list(line, list, x, y));
}

char	*remove_char(char *str, char c)
{
	char	*new;
	char	*spot;

	if (ft_strchr(str + 1, c))
	{
		new = ft_strdup(str + 1);
		while ((spot = ft_strchr(new, c)))
		{
			*spot = '\0';
			ft_strcat(new, spot + 1);
			spot = NULL;
		}
		spot = ft_strdup(new);
		free(new);
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

void	replace_tilde(t_list *list, char **env)
{
	t_list	*tmp;
	char	*str;
	char	*home;
	int		x;

	str = NULL;
	home = NULL;
	tmp = list;
	while (tmp)
	{
		if (*((char*)tmp->content) == '~' && (home = get_in_env(env, "HOME")))
		{
			str = ft_strdup(tmp->content);
			*str = *home;
			x = 0;
			while (++x < (int)ft_strlen(home))
				str = ft_strinsert(str, *(home + x), x);
			free(tmp->content);
			tmp->content = str;
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
	replace_tilde(list, *env);
	return (list);
}
