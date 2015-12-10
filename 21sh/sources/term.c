/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/26 17:33:37 by anowak            #+#    #+#             */
/*   Updated: 2015/12/10 19:50:08 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	write_to_history(char *str, char ***env)
{
	int	fd;
	char *path;

	if (str && ft_strlen(str))
	{
		path = ft_strnew(ft_strlen("~/.zshrc_history")
						 + ft_strlen(get_in_env(*env, "HOME")));
		ft_strcat(path, get_in_env(*env, "HOME"));
		ft_strcat(path, "/.zshrc_history");
		if ((fd = open(path, O_WRONLY | O_CREAT | O_APPEND , 0644)) == -1)
			ft_putendl_fd("Error: Open failed", 2);
		else
		{
			ft_putstr_fd(": ", fd);
			ft_putnbr_fd(time(NULL), fd);
			ft_putstr_fd(":0;", fd);
			ft_putendl_fd(str, fd);
			close(fd);
		}
		free(path);
	}
}

char	**get_history(char **history)
{
	int		fd;
	char	*line;
	char	*path;
	t_list	*list;
	int		ret;

	line = ft_strnew(1);
	list = NULL;
	history = NULL;
	ret = 1;
	path = ft_strnew(ft_strlen("~/.zshrc_history") + ft_strlen(getenv("HOME")));
	ft_strcat(path, getenv("HOME"));
	ft_strcat(path, "/.zshrc_history");
	if ((fd = open(path, O_RDONLY , 0444)) == -1)
		ft_putendl_fd("Error: Open failed", 2);
	while ((ret = get_next_line(fd, &line)))
	{
		ft_lstaddend(&list, ft_lstnew(line, ft_strlen(line)));
		if (!*line)
			break ;
	}
	close(fd);
	history = ft_lsttotab(&list);
	return (history);
}

void	replace_line_with_history(int *pos, char **line, char **history, int index)
{
	tputs(tgetstr("cr", NULL), 0, ft_outc);
	write_prompt(NULL);
	if (index)
	{
		ft_putstr(history[(ft_tablen(history) - index)] + 15);
		if (*line)
			free(*line);
		*line = ft_strdup(history[(ft_tablen(history) - index)] + 15);
		*pos = ft_strlen(*line);
	}
	else
	{
		if (*line)
			free(*line);
		*pos = 0;
	}
	tputs(tgetstr("ce", NULL), 0, ft_outc);
}

void	navigate_through_history(char *key, int *pos, char **line)
{
	static int		index;
	static char		**history;

	(void)line;
	if (key[0] == 10)
	{
		index = 0;
		if (history && *history)
			ft_tabfree(history);
		history = NULL;
		return ;
	}
	if (!history)
		history = get_history(history);
	if (!ft_strcmp(key, tgetstr("ku", NULL)))
	{
		if (ft_tablen(history) > index)
			index++;
		replace_line_with_history(pos, line, history, index);
	}
	else if (!ft_strcmp(key, tgetstr("kd", NULL)) && index > 0)
	{
		index--;
		replace_line_with_history(pos, line, history, index);
	}
}

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
	if (key[1])
		if (key[1] == 91)
			key[1] = 79;
	if (!*line)
		*line = ft_strnew(0);
	if (!ft_strcmp(key, tgetstr("ku", NULL)) || !ft_strcmp(key, tgetstr("kd", NULL)))
		navigate_through_history(key, pos, line);
	else if (!ft_strcmp(key, tgetstr("kr", NULL)) && ft_strlen(*line) > (size_t)pos[0])
	{
		pos[0]++;
		tputs(tgetstr("nd", NULL), 0, ft_outc);
	}
	else if (!ft_strcmp(key, tgetstr("kl", NULL)) && pos[0])
	{
		pos[0]--;
		tputs(tgetstr("le", NULL), 0, ft_outc);
	}
	return (0);
}

int		term_line_len(int n, char **line)
{
	char *str;
	char *next;

	str = *line;
	while (n--)
	{
		str = ft_strchr(str, '\n');
		if (str == NULL)
			return (0);
	}
	if ((next = ft_strchr(str, '\n')))
		return (next - str);
	else
		return (ft_strlen(str));

}

int		term_line_index(int *pos, char **line)
{
	int	i;
	int	tot;

	i = 0;
	tot = 0;
	if (!pos[1])
		return (pos[0]);
	while (i <= pos[1])
	{
		tot += term_line_len(i, line);
		i++;
	}
	tot += pos[0];
	printf("TERM LINE INDEX - pos %d/%d : %d\n", pos[1], pos[0], tot);
	return (tot);
}

int		delete_char(int *pos, char **line)
{
	char	*str;

	if (!*line)
		*line = ft_strnew(0);
	str = *line;
	if (!pos[1] && !pos[0])
		return (0);
	tputs(tgetstr("le", NULL), 0, ft_outc);
	tputs(tgetstr("dm", NULL), 0, ft_outc);
	tputs(tgetstr("dc", NULL), 0, ft_outc);
	tputs(tgetstr("ed", NULL), 0, ft_outc);
	if (pos[0] > 0)
		pos[0]--;
	else if (pos[1] > 0)
	{
		pos[1]--;
		pos[0] = term_line_len(pos[1], line);
	}
	*line = ft_strdelchar(*line, term_line_index(pos, line));
// DELETE THE THINGS
//	str[*pos[0] - 1] = '!';
	return (0);
}

int		process_key(char *key, char **line, int *pos)
{
	if (!key)
		return (0);
	if (key[0] == 10)
	{
		navigate_through_history(key, pos, line);
		*line = ft_strinsert(*line, *key, ft_strlen(*line));
		tputs(tgetstr("ll", NULL), 0, ft_outc);
		ft_putstr(key);
		pos[0]++;
		return (1);
	}
	else if (key[0] == 27)
		return (process_special_key(key, pos, line));
	else if (key[0] == 127)
		return (delete_char(pos, line));
	*line = ft_strinsert(*line, *key, pos[0]);
	if ((pos[1] ? pos[0] : pos[0] + PROMPTLEN) == tgetnum("co"))
	{
		pos[1]++;
		pos[0] = 0;
		ft_putendl("newline");
	}
	tputs(tgetstr("im", NULL), 0, ft_outc);
	tputs(tgetstr("ic", NULL), 0, ft_outc);
	ft_outc(*key);
	tputs(tgetstr("ip", NULL), 0, ft_outc);
	tputs(tgetstr("ei", NULL), 0, ft_outc);
	pos[0]++;
	return (0);
}
