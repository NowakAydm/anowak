/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 18:06:46 by anowak            #+#    #+#             */
/*   Updated: 2016/01/19 16:29:25 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	write_to_history(char *str)
{
	int		fd;
	char	*path;
	int		x;

	if (str && ft_strlen(str))
	{
		path = ft_strnew(ft_strlen("~/.zshrc_history")
						 + ft_strlen(getenv("HOME")));
		ft_strcat(path, getenv("HOME"));
		ft_strcat(path, "/.zshrc_history");
		if ((fd = open(path, O_WRONLY | O_CREAT | O_APPEND , 0644)) == -1)
			ft_putendl_fd("Error: Open failed", 2);
		else
		{
			ft_putstr_fd(": ", fd);
			ft_putnbr_fd(time(NULL), fd);
			ft_putstr_fd(":0;", fd);
			x = 0;
			while (str[x])
			{
				if (str[x] == '\n')
					write(fd, "\\", 1);
				write(fd, str + x, 1);
				x++;
			}
			write(fd, "\n", 1);
			close(fd);
		}
		free(path);
	}
}
/*
char	*add_next_line(char **line, int fd)
{
	int		ret;
	char	*nextl;
	char	*dup;

	ret = 1;
	nextl = NULL;
	if ((ret = get_next_line(fd, &nextl)))
	{
		dup = ft_strnew(ft_strlen(*line) + ft_strlen(nextl) + 1);
		ft_strncpy(dup, *line, ft_strlen(*line) - 1);
		ft_strcat(dup, "\n");
		ft_strncat(dup, nextl, ft_strlen(nextl) - 1);
		free(*line);
		*line = dup;
	}
	return (*line);
}
*/
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
	path = ft_strnew(ft_strlen("~/.zshrc_history") + ft_strlen(getenv("HOME")));
	ft_strcat(path, getenv("HOME"));
	ft_strcat(path, "/.zshrc_history");
	if ((fd = open(path, O_RDONLY , 0444)) == -1)
		ft_putendl_fd("Error: Open failed", 2);
	while ((ret = get_next_line(fd, &line)))
	{
//		while (*(line + ft_strlen(line) - 1) == '\\')
//			add_next_line(&line, fd);
		ft_lstaddend(&list, ft_lstnew(line, ft_strlen(line)));
		if (!*line)
			break ;
	}
	close(fd);
	history = ft_lsttotab(&list);
	return (history);
}

void	replace_line_with_history(int *pos, char **line, char **history, int index)
{
	go_to_endl(pos, line);
	tputs(tgetstr("cr", NULL), 0, ft_outc);
	while (pos[1]-- > 0)
	{
		tputs(tgetstr("cd", NULL), 0, ft_outc);
		tputs(tgetstr("up", NULL), 0, ft_outc);
	}
	write_prompt(NULL);
	if (index && ft_strlen(history[(ft_tablen(history) - index)]) > 15)
	{
		pos[0] = 0;
		pos[1] = 0;
		ft_putstr(history[(ft_tablen(history) - index)] + 15);
		*line = ft_strdup(history[(ft_tablen(history) - index)] + 15);

		int x = 0;
		while (x <= (int) ft_strlen(*line))
		{
			pos[0]++;
			x++;
			if ((pos[1] ? pos[0]: pos[0] + PROMPTLEN) == tgetnum("co"))
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
	else
	{
		if (**line)
		{
			free(*line);
			*line = ft_strdup("");
		}
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
