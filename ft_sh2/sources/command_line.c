/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/13 16:43:45 by anowak            #+#    #+#             */
/*   Updated: 2015/10/26 16:58:32 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

char	*recover_previous_line(char **line, char **tmp)
{
	char *new;

	if (!*tmp)
		return (*line);
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
	char	*line;
	char	*tmp;
	int		ret;

	line = NULL;
	tmp = NULL;
	ret = 1;
	while ((ret = get_next_line_singlefd(0, &line)) != 0)
	{
		if (ret == -1)
		{
			if (tmp)
				free(tmp);
			return (NULL);
		}
		line = recover_previous_line(&line, &tmp);
		if (line)
		{
			if ((ret = check_quotes_in_line(line)) == 0
				&& (ret = check_pipe(line)) == 0
				&& (ret = check_parenthesis(line)) == 0)
				return (line);
			tmp = line;
			line = NULL;
		}
	}
	return ((write(1, "\n", 1) ? NULL : NULL));
}

int		get_heredoc(t_cmd *cmd)
{
	char	*line;
	int		ret;

	line = NULL;
	ret = 1;
	while (ft_strcmp(line, cmd->heredoc) != 0)
	{
		ft_putstr("heredoc > ");

//TODO : CTRL-c during heredoc input

		ret = get_next_line_singlefd(0, &line);
		if (ret == -1)
			return (-1);
		if (ft_strcmp(line, cmd->heredoc) != 0)
			ft_lstaddend(&(cmd->heredoc_list), ft_lstnew(line, ft_strlen(line)));
	}
	return (0);
}

void	add_input_redirection(t_cmd *cmd, char *arg)
{
	int x;

	x = 1;
	if (ft_strcmp(arg, "<") == '<')
	{
		x++;
		while (ft_isspace(arg[x]))
			x++;		
		cmd->heredoc = ft_strdup((char*)(arg + x));
		get_heredoc(cmd);
		pipe(cmd->heredoc_pipe);
	}
	else if (*arg == '<')
	{
		if ((char*)cmd->input_file)
			free((char*)cmd->input_file);
		while (ft_isspace(arg[x]))
			x++;
		cmd->input_file = ft_strdup(arg + x);
	}

}

void	add_output_redirection(t_cmd *cmd, char *arg)
{
	int x;

	x = 1;
//	if (arg[0] == '1')
//		x++;
	if (ft_strcmp(arg, ">") == '>')
	{
		x++;
		while (ft_isspace(arg[x]))
			x++;
		if (arg[x])
			ft_lstadd(&cmd->out_append, ft_lstnew((char*)(arg + x), ft_strlen((char*)(arg + x))));
	}
	else if (*arg == '>')
	{
		while (ft_isspace(arg[x]))
			x++;
		if (arg[x])
			ft_lstadd(&cmd->out, ft_lstnew((char*)(arg + x), ft_strlen((char*)(arg + x))));
	}
	else if (ft_isdigit(*arg) && ft_strcmp(arg + 1, ">&") == '-')
		ft_lstadd(&cmd->to_close, ft_lstnew((char*)arg, 1));
	else if (ft_isdigit(*arg) && ft_isdigit(ft_strcmp(arg + 1, ">&")))
	{
		ft_putendl(arg);
		ft_lstadd(&cmd->to_redirect, ft_lstnew((char*)arg, 4));
	}
}


t_list	*add_to_command_list(t_list *list, t_list *args, int pipe)
{
	t_list	*new;

	new = ft_lstnew(NULL, sizeof(t_cmd*));
	if (!(new->content = ft_memalloc(sizeof(t_cmd))))
		return (NULL);
	((t_cmd*)new->content)->input_file = NULL;
	((t_cmd*)new->content)->heredoc = NULL;
	((t_cmd*)new->content)->out = NULL;
	((t_cmd*)new->content)->out_append = NULL;
	while (*(char*)(args->content) == '<' || *(char*)(args->content) == '>'
		   || arg_is_fd_redirector((char*)(args->content)))
	{
		if (!((t_cmd*)new->content)->input_file && !((t_cmd*)new->content)->heredoc)
			add_input_redirection(new->content, args->content);
		if (!((t_cmd*)new->content)->out_append && !((t_cmd*)new->content)->out)
			add_output_redirection(new->content, args->content);
		if (arg_is_fd_redirector((char*)(args->content)))
			add_output_redirection(new->content, args->content);
		
		if (!(args = args->next))
		{
			ft_lstdel(&new, ft_lstdelcontent);
			return (NULL);
		}
	}
	((t_cmd*)new->content)->argv = ft_lsttotab(&args);
	((t_cmd*)new->content)->argc = ft_tablen(((t_cmd*)new->content)->argv);
	((t_cmd*)new->content)->is_builtin = 0;
	((t_cmd*)new->content)->pipe = pipe;
	ft_lstaddend(&list, new);
	return (list);
}

t_list	*process_command_line(char *line, char ***env_dup, int ret)
{
	t_list	*args;
	t_list	*cmds;
	t_list	*cur;
	t_list	*new_cmd;

	if (!(args = split_into_args(line, env_dup, ret)))
		return (NULL);
	cmds = NULL;
	new_cmd = NULL;
	cur = args;
	while (cur)
	{
		if (ft_strcmp(cur->content, ";") == 0)
		{
			if (ft_lstlen(&new_cmd))
				if (!(cmds = add_to_command_list(cmds, new_cmd, 0)))
					return (NULL);
			ft_lstdel(&new_cmd, ft_lstdelcontent);
		}
		else if (ft_strcmp(cur->content, "|") == 0)
		{
			if (ft_lstlen(&new_cmd))
				if (!(cmds = add_to_command_list(cmds, new_cmd, 1)))
					return (NULL);
			ft_lstdel(&new_cmd, ft_lstdelcontent);			
		}
		else if (*(char*)(cur->content) == '<' || *(char*)(cur->content) == '>')
			ft_lstadd(&new_cmd, ft_lstnew(cur->content, ft_strlen(cur->content)));
		else if (arg_is_fd_redirector((char*)cur->content))
			ft_lstadd(&new_cmd, ft_lstnew(cur->content, ft_strlen(cur->content)));
		else
			ft_lstaddend(&new_cmd, ft_lstnew(cur->content, ft_strlen(cur->content)));
		cur = cur->next;
	}
	if (ft_lstlen(&new_cmd))
		if (!(cmds = add_to_command_list(cmds, new_cmd, 0)))
			return (NULL);
	ft_lstdel(&new_cmd, ft_lstdelcontent);
	ft_lstdel(&args, ft_lstdelcontent);
	return (cmds);
}

int		execute_command_line(t_ftsh *sh, char ***env_dup)
{
	t_list	*list;
	t_list	*tmp;
	int		ret;

	ret = 0;
	list = NULL;
	if (!(list = process_command_line(sh->line, env_dup, sh->ret)))
		return (1);
	while (list)
	{
		while (((t_cmd*)list->content)->pipe)
		{
			tmp = list->next;
			((t_cmd*)tmp->content)->piped_to = list->content;
			list = tmp;
		}
		ret = execute_command(list->content, sh, env_dup);
		tmp = list->next;
		ft_lstdelone(&list, ft_lstdelcontent);
		list = tmp;
	}
	return (ret);
}
