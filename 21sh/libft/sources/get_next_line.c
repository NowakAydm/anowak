/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/27 19:16:07 by anowak            #+#    #+#             */
/*   Updated: 2015/12/09 19:40:29 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*gnl_check_fd(int fd)
{
	static t_list	*list;
	t_list			*tmp;
	t_list			*new_lst;

	if (!list)
		list = ft_lstnew(ft_lstnew(&fd, sizeof(int)), sizeof(t_list));
	tmp = list;
	while (tmp)
	{
		if (*(int*)((t_list*)tmp->content)->content == fd)
			return (tmp->content);
		tmp = tmp->next;
	}
	new_lst = ft_lstnew(ft_lstnew(&fd, sizeof(int)), sizeof(t_list));
	ft_lstadd(&list, new_lst);
	return (new_lst->content);
}

int		gnl_get_str(t_list *cur, char **line)
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

int		gnl_read_next_line(int fd, t_list *cur, char **line)
{
	char	*buf;
	int		ret;

	buf = ft_strnew(BUFF_SIZE);
	ret = read(fd, buf, BUFF_SIZE);
	if (ret == -1 || BUFF_SIZE < 1)
		return (-1);
	*line = ft_strjoin(*line, buf);
	ft_strdel(&buf);
	cur->next = ft_lstsplit(*line, '\n', 1);
	if (ret == 0)
	{
		if (**line)
		{
			ft_lstdelone(&cur->next, ft_lstdelcontent);
			return (2);
		}
		return (1);
	}
	return (0);
}

int		get_next_line(int const fd, char **line)
{
	t_list			*cur;
	int				ret;

	ret = 0;
	if (!line)
		return (-1);
	if (*line)
		ft_strclr(*line);
	cur = gnl_check_fd(fd);
	if (!cur)
		return (-1);
	while (!ret && !(ret = gnl_get_str(cur, line)))
	{
		ret = gnl_read_next_line(fd, cur, line);
		if (ret == -1)
			return (-1);
	}
	ft_strclr(ft_strchr(*line, '\n'));
	return (ret - 1);
}
