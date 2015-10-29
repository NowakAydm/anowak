/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_singlefd.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/14 11:59:53 by anowak            #+#    #+#             */
/*   Updated: 2015/07/14 16:08:59 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		get_str(t_list *cur, char **line)
{
	t_list	*tmp;

	if (!(cur->next))
		return (0);
	if (!ft_strchr((char *)(cur->next)->content, '\n'))
	{
		*line = ft_strdup((cur->next)->content);
		ft_lstdelone(&(cur->next), ft_lstdelcontent);
		return (0);
	}
	tmp = cur->next;
	*line = ft_strdup(tmp->content);
	cur->next = (cur->next)->next;
	ft_lstdelone(&tmp, ft_lstdelcontent);
	return (2);
}

int		read_next_line(int fd, t_list *cur, char **line)
{
	char	*buf;
	char	*new;
	int		ret;

	buf = ft_strnew(BUFF_SIZE);
	ret = read(fd, buf, BUFF_SIZE);
	if (ret == -1 || BUFF_SIZE < 1)
		return (-1);
	if (ret == 0)
	{
		if (*line)
		{
			ft_lstdelone(&(cur->next), ft_lstdelcontent);
			return (2);
		}
		return (1);
	}
	new = ft_strjoin(*line, buf);
	free(buf);
	free(*line);
	*line = NULL;
	cur->next = ft_lstsplit(new, '\n', 1);
	free(new);
	return (0);
}

int		get_next_line_singlefd(int const fd, char **line)
{
	t_list			*list;
	int				ret;

	ret = 0;
	if (!line)
		return (-1);
	if (*line)
		ft_strclr(*line);
	list = ft_lstnew(NULL, 0);
	while (!ret && !(ret = get_str(list, line)))
	{
		ret = read_next_line(fd, list, line);
		if (ret == -1)
		{
			ft_lstdel(&list, ft_lstdelcontent);
			return (-1);
		}
	}
	if (*line)
		ft_strclr(ft_strchr(*line, '\n'));
	ft_lstdel(&list, ft_lstdelcontent);
	return (ret - 1);
}
