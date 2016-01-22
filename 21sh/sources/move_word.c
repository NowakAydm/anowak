/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 20:42:09 by anowak            #+#    #+#             */
/*   Updated: 2016/01/22 20:42:33 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	go_to_prevword(int *pos, char **line)
{
	if (ft_isspace(*(*line + term_line_index(pos, line) - 1)))
		while (ft_isspace(*(*line + term_line_index(pos, line) - 1))
				&& term_line_index(pos, line))
			process_left_arrow(pos, line);
	while (!ft_isspace(*(*line + term_line_index(pos, line) - 1))
			&& term_line_index(pos, line))
		process_left_arrow(pos, line);
}

void	go_to_nextword(int *pos, char **line)
{
	if (!ft_isspace(*(*line + term_line_index(pos, line))))
		while (!ft_isspace(*(*line + term_line_index(pos, line)))
				&& term_line_index(pos, line) < (int)ft_strlen(*line))
			process_right_arrow(pos, line);
	while (ft_isspace(*(*line + term_line_index(pos, line)))
			&& term_line_index(pos, line) < (int)ft_strlen(*line))
		process_right_arrow(pos, line);
}
