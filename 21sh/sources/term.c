/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/26 17:33:37 by anowak            #+#    #+#             */
/*   Updated: 2016/01/22 20:42:29 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	restore_term(struct termios *term_bak)
{
	static struct termios	*term;
	static unsigned long	i;
	static unsigned long	o;
	static unsigned long	c;
	static unsigned long	l;

	if (term_bak)
	{
		term = term_bak;
		i = term_bak->c_iflag;
		o = term_bak->c_oflag;
		c = term_bak->c_cflag;
		l = term_bak->c_lflag;
	}
	else if (term)
	{
		term->c_iflag = i;
		term->c_oflag = o;
		term->c_cflag = c;
		term->c_lflag = l;
		term->c_cc[VMIN] = 1;
		term->c_cc[VTIME] = 0;
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

int		term_line_len(int n, char **line)
{
	char	*str;
	int		x;
	int		flag;
	int		start;

	x = 0;
	flag = n;
	start = 0;
	str = *line;
	while (str[x])
	{
		if (!((!flag && n < flag ? x : x + PROMPTLEN) % tgetnum("co"))
			|| str[x] == '\n')
		{
			x++;
			if (!n)
				return (x - start);
			start = x;
			n--;
			flag = 0;
		}
		x++;
	}
	return (0);
}

int		term_line_index(int *pos, char **line)
{
	int	i;
	int	tot;

	i = 0;
	tot = 0;
	while (i < pos[1])
	{
		tot += term_line_len(i, line);
		i++;
	}
	tot += pos[0];
	if (!pos[1])
		return (pos[0]);
	return (tot);
}

int		process_key(char *key, char **line, int *pos)
{
	if (!key)
		return (0);
	if (key[0] == 4)
	{
		ft_strclr(*line);
		key[0] = 10;
	}
	if (key[0] == 10)
		return (process_enter(key, line, pos));
	else if (key[0] == 27 || key[0] == 1 || key[0] == 5)
		return (process_special_key(key, pos, line));
	else if (key[0] == 11 || key[0] == 25)
		return (process_copypaste(key, pos, line));
	else if (key[0] == 127)
		return (delete_char(pos, line));
	else if (ft_isprint(key[0]))
		insert_key(key, line, pos);
	if (!*line)
		*line = ft_strnew(0);
	return (0);
}
