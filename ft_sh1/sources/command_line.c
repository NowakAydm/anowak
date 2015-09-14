/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/13 16:43:45 by anowak            #+#    #+#             */
/*   Updated: 2015/05/20 15:07:41 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

int	check_quotes_in_line(char *line)
{
	int	x = 0;
	int	ret = 0;
	
	while (line[x])
    {
		if (line[x] == '\'' || line[x] == '"' || line[x] == '`')
		{
			ret = line[x++];
			while (line[x] && line[x] != ret)
				if (line[x++] == '\\')
					x++;
			if (!(line[x]))
			{
				if (ret == '"')
					write(1, "dquote> ", 9);
				else if (ret == '\'')
					write(1, "quote> ", 8);
				else if (ret == '`')
					write(1, "bquote> ", 9);
				return (ret);
			}
			else
				ret = 0;
		}
		else if (line[x] == '\\')
		{
			if (!(line[x + 1]))
			{
				write(1, "> ", 2);
				return (1);
			}
			x++;
		}
		x++;
    }
	return (ret);
}

char	*recover_previous_line(char **line, char **tmp)
{
	char *new;
	
	if (!(new = ft_strnew(ft_strlen(*tmp) + ft_strlen(*line) + 1)))
		return (NULL);
	ft_strcpy(new, *tmp);
	if (new[ft_strlen(new) - 1] != '\\' || !(**line))
		ft_strcat(new, "\n");
	ft_strcat(new, *line);
	free(*line);
	free(*tmp);
	*line = new;
	*tmp = NULL;
	return (*line);
}

char	*get_command_line(void)
{
	char *line;
	char *tmp = NULL;
	
	int ret = 1;
	line = NULL;
	
	printf("\n>>>> GET Command line STARTS\n");
	while ((ret = get_next_line(0, &line)) != 0)
	{
		printf("---- GNL read a line\n       ret = %d | line = '%s'\n", ret, line);
		if (tmp)
		{
			printf("---- recovered previous line\n       pre  '%s'\n", tmp);
			line = recover_previous_line(&line, &tmp);
			printf("       post '%s'\n", line);
		}
		if (ret == -1)
			break ;
		if (line)
		{
			if ((ret = check_quotes_in_line(line)) == 0)
			{
				printf("<<<< no quote problem returning '%s'\n", line);
				return (line);
			}
			tmp = line;
			line = NULL;
		}
	}
	if (ret == -1)
	{
		printf("XXXX Get next line rturned -1\n");
		exit(1);
	}
	if (tmp)
		free(tmp);
	return (NULL);
}

char	**split_into_args(char *line)
{
	t_list	*list = NULL;
	char	*str = NULL;
	char	**tab = NULL;
	int		x = 0;
	int		y = 0;
	int		c = 0;
	
	printf(">>>> SPLIT INTO ARGS STARTS\n");
	while (line[x])
	{
		printf("---- loop start - x = %d\n", x);
		y = 0;
		while (ft_isspace(line[x]))
			x++;
		printf("---- skipped spaces - x = %d\n", x);
		if (ft_isquote(line[x]))
		{
			c = line[x];
			printf("---- theres a quote : line[%d] = '%c'\n", x, c);
			x++;
			while (line[x + y] && line[x + y] != c)
				if (line[x + y++] == '\\')
					y++;
			printf("---- skipped chars - y = %d\n", y);
			if (!(line [x + y]))
			{
				printf("<<<< RETURNING NULL Error : missing a quote\n");
				return (NULL);
			}
			else if (y++)
			{
				if (!(str = ft_strndup((line + x), y - 1)))
					return (NULL);
				printf("---- found another quote, adding to list\n      arg = |%s|\n", str);
				ft_lstaddend(&list, ft_lstnew(str, ft_strlen(str) + 1));
			}
		}
		else if (line[x])
		{
			if (line[x] == '\\' && line[x + 1])
			{
				x++;
				y++;
				printf("---- skipped backslash - x = %d y = %d\n", x, y);
			}
			printf("---- no quote, new arg - start = %d\n", x);
			while (line[x + y] && !(ft_isspace(line[x + y])))
				if (line[x + y++] == '\\')
					y++;
			if (y)
			{
				if (!(str = ft_strndup((line + x), y)))
					return (NULL);
				printf("     x = %d | y = %d\n", x, y);
				printf("---- ft_isspace returned 1, adding to list - arg = |%s|\n", str);
				ft_lstaddend(&list, ft_lstnew(str, ft_strlen(str) + 1));
			}
		}
		str = NULL;
		x += y;
	}
	if (!list)
	ft_putendl("XXXX            NO LIST");
	else
	{
		printf("XXXX       len = %d    LIST = \n", ft_lstlen(&list));
		ft_putlst_str(&list);
		ft_putendl("\n");
	}
	if (list)
		tab = ft_lsttotab(&list);
	ft_lstdel(&list, ft_lstdelcontent);
	return (tab);
}

t_cmd	*process_command_line(char *line)
{
	t_cmd	*new;

	if(!(new = (t_cmd*)malloc(sizeof(t_cmd))))
		return (NULL);
#ifdef VERBOSE
	printf("\n______-------  NEW COMMAND LINE    -------_______\n");
	printf("|%s|\n", line);
	printf("\n");
#endif
	if (!(new->argv = split_into_args(line)))
	{
		printf("<<<< Error : split_into_args RETURNED NULL\n");			
		return (NULL);
	}
	new->argc = ft_tablen(new->argv);

//	replace tilde by HOME
//	delete all backslash
	
#ifdef VERBOSE
	printf("new->ac = %d\n", new->argc);
	int x = -1;
	
	while (new->argv[++x])
		printf("new->av[%d] = '%s'\n", x, new->argv[x]);
	printf("new->av[%d] = '%s'\n", x, new->argv[x]);
	printf("\n");
#endif
	return (new);
}
