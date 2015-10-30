/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/26 17:33:37 by anowak            #+#    #+#             */
/*   Updated: 2015/10/30 17:29:02 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	restore_term(struct termios *term_bak)
{
	static struct termios *term;

	if (term_bak)
		term = term_bak;
	else
		tcsetattr(0, TCSANOW, term);
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

int		read_next_char(char **line)
{
	int		ret;
	char	*buf;
	char	*new;

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
	if (!(new = ft_strjoin(*line, buf)))
		return (-1);
	free(*line);
	free(buf);
	*line = new;
	return (0);
}

int		read_next_line(char **line)
{
	int ret;

	ret = 1;
	if (!line)
		return (-1);
	if (*line)
		ft_strclr(*line);
	while (ret)
	{
		if ((ret = read_next_char(line)) == -1)
			return (-1);
		if (!(ft_strchr(*line, '\n')))
			ret = 1;
	}
	return (1);
}

int		process_key(char *key)
{
	int	x;

	x = 0;
	if (key[0] == 27)
	{
		free(key);
		return (0);
	}
	ft_putstr(key);
/*	while (key[x])
	{
		if (x)
			ft_putstr(" - ");
		ft_putnbr(key[x]);
		x++;
	}
	ft_putstr("\n");*/
	return (0);
}
