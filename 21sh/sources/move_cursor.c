/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 20:35:08 by anowak            #+#    #+#             */
/*   Updated: 2016/01/22 20:36:26 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	go_up_aline(int *pos, char **line)
{
	if (pos[1])
	{
		pos[1]--;
		if (!pos[1])
			pos[0] -= PROMPTLEN - 1;
		tputs(tgetstr("up", NULL), 0, ft_outc);
	}
	else
		go_to_begl(pos, line);
}

void	go_down_aline(int *pos, char **line)
{
	int x;

	x = 0;
	if (!pos[1])
		x++;
	while (x++ <= tgetnum("co"))
		process_right_arrow(pos, line);
}

void	go_to_endl(int *pos, char **line)
{
	while ((int)ft_strlen(*line) > term_line_index(pos, line)
			&& ft_strlen(*line))
		process_right_arrow(pos, line);
}

void	go_to_begl(int *pos, char **line)
{
	while (pos[0] || pos[1])
		process_left_arrow(pos, line);
}
