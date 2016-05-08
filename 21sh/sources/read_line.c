/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 20:38:57 by anowak            #+#    #+#             */
/*   Updated: 2016/01/22 20:41:31 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int		read_next_char(char **line, int *pos)
{
	int		ret;
	char	*buf;

	clear_line(line);
	if (!(buf = ft_strnew(8)))
		return (-1);
	ret = read(0, buf, 8);
	if (ret == -1)
		return (-1);
	if (ret == 0)
	{
		free(buf);
		if (*line)
			return (2);
		return (1);
	}
	process_key(buf, line, pos);
	if (!*line)
		return (-1);
	free(buf);
	return (0);
}

void	clear_line(char **line)
{
	static char **save;

	if (line)
		save = line;
	else
		ft_strdel(save);
}

int		read_next_line(char **line)
{
	int ret;
	int *pos;

	pos = ft_memalloc(sizeof(int) * 2);
	ret = 1;
	if (!line)
		return (-1);
	if (*line)
		ft_strclr(*line);
	while (ret)
	{
		if ((ret = read_next_char(line, pos)) == -1)
		{
			free(pos);
			return (-1);
		}
		if (!(ft_strchr(*line, '\n')))
			ret = 1;
	}
	*(*line + ft_strlen(*line) - 1) = 0;
	free(pos);
	return (1);
}

int		ft_outc(int c)
{
	if (!ft_isascii(c))
		return (0);
	if (write(1, &c, 1))
		return (1);
	return (0);
}

int		process_enter(char *key, char **line, int *pos)
{
	navigate_through_history(key, pos, line);
	*line = ft_strinsert(*line, *key, ft_strlen(*line));
	tputs(tgetstr("ll", NULL), 0, ft_outc);
	ft_putstr("\n");
	pos[0]++;
	while (term_line_len(++pos[1], line))
		tputs(tgetstr("do", NULL), 0, ft_outc);
	return (1);
}
