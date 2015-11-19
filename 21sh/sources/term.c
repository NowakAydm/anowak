/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/26 17:33:37 by anowak            #+#    #+#             */
/*   Updated: 2015/11/19 17:57:38 by anowak           ###   ########.fr       */
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
//	char	*new;

//	printf("POS %d - %d\n", pos[0], pos[1]);
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

int		ft_outc(int c)
{
	if (!ft_isascii(c))
		return (0);
	if (write(1, &c, 1))
		return (1);
	else
		return (0);
}

void	blblbl(char *str)
{
	int x = 0;

	while (str[x])
	{
		if (x)
			ft_putstr(" - ");
		ft_putnbr(str[x++]);
	}
}

int		process_special_key(char *key, int *pos, char **line)
{	
	ft_putstr("key : ");
	blblbl(key);
	ft_putstr(" | left : ");
	blblbl(tgetstr("kl", NULL));
	ft_putstr(" | right : ");
	blblbl(tgetstr("kr", NULL));
	ft_putendl("");
	if (!ft_strcmp(key, tgetstr("kr", NULL)) && ft_strlen(*line) > (size_t)pos[0])
	{
		pos[0]++;
		tputs(tgetstr("nd", NULL), 0, ft_outc);
	}
	if (!ft_strcmp(key, tgetstr("kl", NULL)) && pos[0])
	{
		pos[0]--;
		tputs(tgetstr("le", NULL), 0, ft_outc);
	}
	return (0);
}

int		delete_char(int **pos, char **line)
{
	char	*str;

	str = *line;
	if (*pos[0] == 0)
		return (0);
	tputs(tgetstr("le", NULL), 0, ft_outc);
	tputs(tgetstr("dm", NULL), 0, ft_outc);
	tputs(tgetstr("dc", NULL), 0, ft_outc);
	tputs(tgetstr("ed", NULL), 0, ft_outc);
	*pos[0] = **pos -1;
	*line = ft_strdelchar(*line, *pos[0]);
// DELETE THE THINGS
//	str[*pos[0] - 1] = '!';
	return (0);
}

int		process_key(char *key, char **line, int *pos)
{
	if (!key)
		return (0);
	ft_putstr(tgetstr("im", NULL));
	if (key[0] == 10)
	{
		*line = ft_strinsert(*line, *key, ft_strlen(*line));
		ft_putstr(key);
		tputs(tgetstr("ei", NULL), 0, ft_outc);
		pos[0]++;
		return (1);
	}
	else if (key[0] == 27)
		return (process_special_key(key, pos, line));
	else if (key[0] == 127)
		return (delete_char(&pos, line));
	*line = ft_strinsert(*line, *key, pos[0]);
	tputs(tgetstr("ic", NULL), 0, ft_outc);
	ft_outc(*key);
	tputs(tgetstr("ip", NULL), 0, ft_outc);
	tputs(tgetstr("ei", NULL), 0, ft_outc);
	pos[0]++;
	return (0);
}
