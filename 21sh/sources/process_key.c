/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_key.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 20:27:59 by anowak            #+#    #+#             */
/*   Updated: 2016/01/22 20:33:58 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	process_left_arrow_on_begl(int *pos)
{
	int x;

	x = 0;
	if (!pos[1])
		while (x++ < PROMPTLEN)
			tputs(tgetstr("nd", NULL), 0, ft_outc);
	tputs(tgetstr("up", NULL), 0, ft_outc);
	x = pos[0];
	while (x--)
		tputs(tgetstr("nd", NULL), 0, ft_outc);
	pos[0]--;
}

void	process_left_arrow(int *pos, char **line)
{
	int x;

	x = 0;
	if (pos[0] > 0 || (pos[1] && pos[0] == 0))
	{
		pos[0]--;
		tputs(tgetstr("le", NULL), 0, ft_outc);
	}
	else if (pos[1] && pos[0] == -1)
	{
		tputs(tgetstr("le", NULL), 0, ft_outc);
		pos[1]--;
		pos[0] = term_line_len(pos[1], line);
		pos[0] -= PROMPTLEN - 1;
	}
	else if ((pos[1] ? pos[0] : pos[0] + PROMPTLEN) == tgetnum("co"))
		process_left_arrow_on_begl(pos);
	return ;
}

void	process_right_arrow(int *pos, char **line)
{
	if (ft_strlen(*line) && (int)ft_strlen(*line) > term_line_index(pos, line))
	{
		if (pos[0] + 1 == (pos[1] ? tgetnum("co") : tgetnum("co") - PROMPTLEN))
		{
			pos[0] = -1;
			pos[1]++;
			tputs(tgetstr("do", NULL), 0, ft_outc);
			tputs(tgetstr("cr", NULL), 0, ft_outc);
		}
		else
		{
			pos[0]++;
			tputs(tgetstr("nd", NULL), 0, ft_outc);
		}
	}
	return ;
}

void	process_alt_arrow(char *key, int *pos, char **line)
{
	if (key[1] == 27 && key[2] == 91 && key[3] == 68)
		go_to_prevword(pos, line);
	if (key[1] == 27 && key[2] == 91 && key[3] == 67)
		go_to_nextword(pos, line);
	if (key[1] == 27 && key[2] == 91 && key[3] == 65)
		go_up_aline(pos, line);
	if (key[1] == 27 && key[2] == 91 && key[3] == 66)
		go_down_aline(pos, line);
}

int		process_special_key(char *key, int *pos, char **line)
{
	if (key[3])
		process_alt_arrow(key, pos, line);
	if ((key[1] == 91 && key[2] == 70) || key[0] == 5)
		go_to_endl(pos, line);
	else if ((key[1] == 91 && key[2] == 72) || key[0] == 1)
		go_to_begl(pos, line);
	if (key[1])
		if (key[1] == 91)
			key[1] = 79;
	if (!*line)
		*line = ft_strdup("");
	if (!ft_strcmp(key, tgetstr("ku", NULL))
		|| !ft_strcmp(key, tgetstr("kd", NULL)))
		navigate_through_history(key, pos, line);
	else if (!ft_strcmp(key, tgetstr("kl", NULL)))
		process_left_arrow(pos, line);
	else if (!ft_strcmp(key, tgetstr("kr", NULL)))
		process_right_arrow(pos, line);
	return (0);
}
