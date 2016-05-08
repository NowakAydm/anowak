/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 18:06:46 by anowak            #+#    #+#             */
/*   Updated: 2016/01/22 20:12:12 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	**get_history(char **history)
{
	int		fd;
	char	*line;
	char	*path;
	t_list	*list;
	int		ret;

	line = ft_strnew(1);
	list = NULL;
	history = NULL;
	ret = 1;
	path = ft_strnew(ft_strlen(getenv("HOME")) + 15);
	ft_strcat(path, getenv("HOME"));
	ft_strcat(path, "/.zshrc_history");
	if ((fd = open(path, O_RDONLY, 0444)) == -1)
		ft_putendl_fd("Error: Open failed", 2);
	while ((ret = get_next_line(fd, &line)))
	{
		ft_lstaddend(&list, ft_lstnew(line, ft_strlen(line)));
		if (!*line)
			break ;
	}
	close(fd);
	history = ft_lsttotab(&list);
	return (history);
}

void	history_update_pos(int *pos, char **line)
{
	int x;

	x = 0;
	while (x <= (int)ft_strlen(*line))
	{
		pos[0]++;
		x++;
		if ((pos[1] ? pos[0] : pos[0] + PROMPTLEN) == tgetnum("co"))
		{
			if (pos[1])
				pos[0] = 0;
			else
				pos[0] = -1;
			pos[1]++;
		}
	}
	pos[0]--;
}

void	replace_line_with_history(int *pos, char **line, char **h, int index)
{
	go_to_endl(pos, line);
	tputs(tgetstr("cr", NULL), 0, ft_outc);
	while (pos[1]-- > 0)
	{
		tputs(tgetstr("cd", NULL), 0, ft_outc);
		tputs(tgetstr("up", NULL), 0, ft_outc);
	}
	write_prompt(NULL);
	if (index && ft_strlen(h[(ft_tablen(h) - index)]) > 15)
	{
		pos[0] = 0;
		pos[1] = 0;
		ft_putstr(h[(ft_tablen(h) - index)] + 15);
		*line = ft_strdup(h[(ft_tablen(h) - index)] + 15);
		history_update_pos(pos, line);
	}
	else
	{
		if (**line)
			*line = ft_strdup("");
		pos[0] = 0;
		pos[1] = 0;
	}
	tputs(tgetstr("ce", NULL), 0, ft_outc);
}

void	navigate_through_history(char *key, int *pos, char **line)
{
	static int		index;
	static char		**history;

	(void)line;
	if (key[0] == 10)
	{
		index = 0;
		if (history && *history)
			ft_tabfree(history);
		history = NULL;
		return ;
	}
	if (!history)
		history = get_history(history);
	if (!ft_strcmp(key, tgetstr("ku", NULL)))
	{
		if (ft_tablen(history) > index)
			index++;
		replace_line_with_history(pos, line, history, index);
	}
	else if (!ft_strcmp(key, tgetstr("kd", NULL)) && index > 0)
	{
		index--;
		replace_line_with_history(pos, line, history, index);
	}
}
