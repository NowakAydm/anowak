/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/26 17:33:37 by anowak            #+#    #+#             */
/*   Updated: 2015/11/11 23:04:46 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	restore_term(struct termios *term_bak)
{
	static struct termios	*term;
	static unsigned long	a;

	if (term_bak)
	{
		term = term_bak;
		a = term_bak->c_lflag;
	}
	else if (term)
	{
		term->c_lflag = a;
		tcsetattr(0, TCSADRAIN, term);
	}
}

int		initialize_term(t_ftsh *sh, char **envp)
{
	int				ret;

	if (!(sh->term_name = ft_strdup(get_in_env(envp, "TERM"))))
		return (-1);
	if ((ret = tgetent(NULL, sh->term_name)) != 1)
		return (-1);
	if (isatty(0))
	{
		sh->term = ft_memalloc(sizeof(sh->term));
		sh->term_bak = ft_memalloc(sizeof(sh->term));
		if ((ret = tcgetattr(0, sh->term)) == -1)
			return (-1);
		if ((ret = tcgetattr(0, sh->term_bak)) == -1)
			return (-1);
		restore_term(sh->term_bak);
		(sh->term)->c_lflag &= ~(ICANON);
		(sh->term)->c_lflag &= ~(ECHO);
		(sh->term)->c_cc[VMIN] = 1;
		(sh->term)->c_cc[VTIME] = 0;
		tcsetattr(0, TCSADRAIN, sh->term);
		return (0);
	}
	return (-1);
}

int		read_next_char(char **line, int *pos)
{
	int		ret;
	char	*buf;
	char	*new;

//	printf("POS %d - %d\n", pos[0], pos[1]);
	buf = ft_strnew(8);
	ret = read(0, buf, 8);
	if (ret == -1)
		return (-1);
	if (ret == 0)
	{
		if (*line)
			return (2);
		return (1);			
	}
	if (process_key(buf, line, pos))
	{
		if (!(new = ft_strjoin(*line, buf)))
			return (-1);
		free(*line);
		*line = new;
	}
	free(buf);
	return (0);
}

int		read_next_line(char **line)
{
	int ret;
	int *pos;

	pos = ft_memalloc(sizeof(int) *2);
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
	free(pos);
	return (1);
}

int		process_special_key(char *key, int *pos, char **line)
{
	if (key[1] && key[2])
		if (key[1] == 91)
		{
			if (key[2] == 67 && ft_strlen(*line) > (size_t)pos[0])
			{
				pos[0]++;
				ft_putstr(tgetstr("nd", NULL));
			}
			if (key[2] == 68 && pos[0])
			{
				pos[0]--;
				ft_putstr(tgetstr("le", NULL));
			}
		}
	return (0);
}

int		delete_char(int **pos, char **line)
{
	char	*str;

	str = *line;
	if (!pos[0])
		return (0);
	ft_putstr(tgetstr("le", NULL));
	ft_putstr(tgetstr("dm", NULL));
	ft_putstr(tgetstr("dc", NULL));
	ft_putstr(tgetstr("ed", NULL));
// DELETE THE THINGS
	str[*pos[0] - 1] = '!';
	pos[0]--;
	return (0);
}

int		process_key(char *key, char **line, int *pos)
{
	ft_putstr(tgetstr("im", NULL));
	if (!key)
		return (0);
	if (key[0] == 27)
		return (process_special_key(key, pos, line));
	else if (key[0] == 127)
		return (delete_char(&pos, line));
	ft_putstr(tgetstr("ic", NULL));
	ft_putstr(key);
	ft_putstr(tgetstr("ip", NULL));
	ft_putstr(tgetstr("ei", NULL));
	pos[0]++;
	return (1);
}
