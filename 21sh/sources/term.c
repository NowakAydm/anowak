/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/26 17:33:37 by anowak            #+#    #+#             */
/*   Updated: 2016/01/19 15:33:45 by anowak           ###   ########.fr       */
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
//	printf("line %d - pos %d\n", pos[1], pos[0]);
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
//	printf("A - TERM LINE LEN - line %d\n", n);
	while (str[x])
	{
		if (str[x] == '\n' || !((!flag && n < flag? x : x + PROMPTLEN) % tgetnum("co")))
		{
//			printf("B - n=%d - x=%d - start=%d --> %d\n",n,x,start, x - start);
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
//	printf("TERM LINE INDEX - pos %d/%d : %d --> index: %d\n", pos[1], pos[0], tot, tot + pos[0]);
	tot += pos[0];
//	tot += pos[1];

	if (!pos[1])
		return (pos[0]);
	return (tot);
}

void	process_left_arrow(int *pos, char **line)
{
	int x;

	x = 0;
	if (pos[0] > 0)
	{
		pos[0]--;
		tputs(tgetstr("le", NULL), 0, ft_outc);
	}
	else if (pos[1] && pos[0] == 0)
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
	else if ((pos[1] ? pos[0]: pos[0] + PROMPTLEN) == tgetnum("co"))
	{
		if (!pos[1])
			while (x++ < PROMPTLEN)
				tputs(tgetstr("nd", NULL), 0, ft_outc);
		tputs(tgetstr("up", NULL), 0, ft_outc);
		x = pos[0];
		while (x--)
			tputs(tgetstr("nd", NULL), 0, ft_outc);
		pos[0]--;
	}
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

void	go_up_aline(int *pos, char **line)
{
	if (pos[1])
	{
		(void) line;
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
	int x = 0;

	if (!pos[1])
		x++;
	while (x++ <= tgetnum("co"))
		process_right_arrow(pos, line);
}

void	go_to_endl(int *pos, char **line)
{
	while (ft_strlen(*line) && (int)ft_strlen(*line) > term_line_index(pos, line))
		process_right_arrow(pos, line);
}

void	go_to_begl(int *pos, char **line)
{
	while (pos[0] || pos[1])
		process_left_arrow(pos, line);
}

void	go_to_prevword(int *pos, char **line)
{
	if (ft_isspace(*(*line + term_line_index(pos, line) - 1)))
		while (ft_isspace(*(*line + term_line_index(pos, line) - 1)) && term_line_index(pos, line))
			process_left_arrow(pos, line);
	while (!ft_isspace(*(*line + term_line_index(pos, line) - 1)) && term_line_index(pos, line))
		process_left_arrow(pos, line);
}

void	go_to_nextword(int *pos, char **line)
{
	if (!ft_isspace(*(*line + term_line_index(pos, line))))
		while (!ft_isspace(*(*line + term_line_index(pos, line)))
			   && term_line_index(pos, line) < (int) ft_strlen(*line))
			process_right_arrow(pos, line);
	while (ft_isspace(*(*line + term_line_index(pos, line)))
		   && term_line_index(pos, line) < (int) ft_strlen(*line))
		process_right_arrow(pos, line);
}


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
//		ft_putendl("copied to clip =");
//		ft_putendl(clip);
	}
	else if (key[0] == 25)
	{
		x = -1;
		while (++x < (int) ft_strlen(clip))
			insert_key(clip + x, line, pos);
	}
	return (0);
}

int		process_special_key(char *key, int *pos, char **line)
{
	if (key[3])
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
	if ((key[1] == 91 && key[2] == 70) || key[0] == 5)
		go_to_endl(pos, line);
	else if ((key[1] == 91 && key[2] == 72) || key[0] == 1)
		go_to_begl(pos, line);
	if (key[1])
		if (key[1] == 91)
			key[1] = 79;
	if (!*line)
		*line = ft_strdup("");
	if (!ft_strcmp(key, tgetstr("ku", NULL)) || !ft_strcmp(key, tgetstr("kd", NULL)))
		navigate_through_history(key, pos, line);
	else if (!ft_strcmp(key, tgetstr("kl", NULL)))
		process_left_arrow(pos, line);
	else if (!ft_strcmp(key, tgetstr("kr", NULL)))
		process_right_arrow(pos, line);
	return (0);
}

int		delete_char(int *pos, char **line)
{
	int		x;
	char	*str;

	x = 0;
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
	{
		tputs(tgetstr("up", NULL), 0, ft_outc);
		pos[1]--;
		pos[0] = term_line_len(pos[1], line) - 1;
		x = pos[0];
		while (x--)
			tputs(tgetstr("nd", NULL), 0, ft_outc);
		if (!pos[1])
			pos[0] -= PROMPTLEN;
	}
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
	if ((pos[1] ? pos[0] + 1: pos[0] + PROMPTLEN) == tgetnum("co"))
	{
		pos[1]++;
//		if (pos[1] > 1)
//			pos[0] = 0;
//		else
			pos[0] = -1;
//		ft_putnbr(pos[0]);
//		ft_putnbr(pos[1]);
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


int		process_key(char *key, char **line, int *pos)
{
	if (!key)
		return (0);
//	blblbl(key);
//	ft_putendl("");
//		printf("%d - %d\n", pos[0], pos[1]);
	if (key[0] == 4)
	{
		ft_strclr(*line);
		key[0] = 10;
	}
	if (key[0] == 10)
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
