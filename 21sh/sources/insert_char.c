/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 20:37:04 by anowak            #+#    #+#             */
/*   Updated: 2016/01/22 20:45:40 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int		process_copypaste(char *key, int *pos, char **line)
{
	static char	*clip;
	int			x;

	if (key[0] == 11)
	{
		if (clip)
			free(clip);
		clip = ft_strdup(*line + term_line_index(pos, line));
		ft_strclr(*line + term_line_index(pos, line));
		tputs(tgetstr("sc", NULL), 0, ft_outc);
		x = ft_strlen(clip);
		while (x--)
			ft_putstr(" ");
		tputs(tgetstr("rc", NULL), 0, ft_outc);
	}
	else if (key[0] == 25)
	{
		x = -1;
		while (++x < (int)ft_strlen(clip))
			insert_key(clip + x, line, pos);
	}
	return (0);
}

void	delete_char_up_aline(int *pos, char **line)
{
	int		x;

	x = 0;
	tputs(tgetstr("up", NULL), 0, ft_outc);
	pos[1]--;
	pos[0] = term_line_len(pos[1], line) - 1;
	x = pos[0];
	while (x--)
		tputs(tgetstr("nd", NULL), 0, ft_outc);
	if (!pos[1])
		pos[0] -= PROMPTLEN;
}

int		delete_char(int *pos, char **line)
{
	char	*str;

	if (!*line)
		*line = ft_strnew(0);
	str = *line;
	if (!pos[1] && !pos[0])
		return (0);
	if (pos[0] >= 0)
	{
		tputs(tgetstr("le", NULL), 0, ft_outc);
		tputs(tgetstr("dm", NULL), 0, ft_outc);
		tputs(tgetstr("dc", NULL), 0, ft_outc);
		tputs(tgetstr("ed", NULL), 0, ft_outc);
		pos[0]--;
	}
	if (pos[1] > 0 && pos[0] == -1)
		delete_char_up_aline(pos, line);
	*line = ft_strdelchar(*line, term_line_index(pos, line));
	tputs(tgetstr("sc", NULL), 0, ft_outc);
	ft_putstr(*line + term_line_index(pos, line));
	ft_putstr("   ");
	tputs(tgetstr("rc", NULL), 0, ft_outc);
	return (0);
}

void	insert_key(char *key, char **line, int *pos)
{
	*line = ft_strinsert(*line, *key, term_line_index(pos, line));
	if ((pos[1] ? pos[0] + 1 : pos[0] + PROMPTLEN) == tgetnum("co"))
	{
		pos[1]++;
		pos[0] = -1;
		ft_putendl("");
	}
	pos[0]++;
	tputs(tgetstr("im", NULL), 0, ft_outc);
	tputs(tgetstr("ic", NULL), 0, ft_outc);
	ft_outc(*key);
	tputs(tgetstr("ip", NULL), 0, ft_outc);
	tputs(tgetstr("ei", NULL), 0, ft_outc);
	if (term_line_index(pos, line) < (int)ft_strlen(*line))
	{
		tputs(tgetstr("sc", NULL), 0, ft_outc);
		ft_putstr(*line + term_line_index(pos, line));
		tputs(tgetstr("rc", NULL), 0, ft_outc);
	}
}
