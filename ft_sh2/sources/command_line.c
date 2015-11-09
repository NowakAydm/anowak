/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/13 16:43:45 by anowak            #+#    #+#             */
/*   Updated: 2015/11/09 21:40:23 by anowak           ###   ########.fr       */
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
	while ((ret = read_next_line(&line)) != 0)
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
			if (!check_everything(line))
				return (line);
			tmp = line;
			line = NULL;
		}
	}
	return (NULL);
}

t_list	*add_to_command_list(t_list *list, t_list *args, int pipe)
{
	t_list	*new;
	t_cmd	*cmd;

	new = ft_lstnew(NULL, sizeof(t_cmd*));
	if (!(new->content = ft_memalloc(sizeof(t_cmd))))
		return (NULL);
	cmd = new->content;
	cmd->input_file = NULL;
	cmd->heredoc = NULL;
	cmd->out = NULL;
	cmd->out_append = NULL;
	while (*(char*)(args->content) == '<' || *(char*)(args->content) == '>'
			|| arg_is_fd_redirector((char*)(args->content)))
		if (!(args = process_redirection(args, cmd)))
		{
			ft_lstdel(&new, ft_lstdelcontent);
			return (NULL);
		}
	cmd->argv = ft_lsttotab(&args);
	cmd->argc = ft_tablen(cmd->argv);
	cmd->is_builtin = 0;
	cmd->pipe = pipe;
	ft_lstaddend(&list, new);
	return (list);
}

int		process_argument(char *arg, t_list **cmds, t_list **new_cmd)
{
	if (ft_strcmp(arg, ";") == 0)
	{
		if (ft_lstlen(new_cmd))
			if (!(*cmds = add_to_command_list(*cmds, *new_cmd, 0)))
				return (1);
		ft_lstdel(new_cmd, ft_lstdelcontent);
	}
	else if (ft_strcmp(arg, "|") == 0)
	{
		if (ft_lstlen(new_cmd))
			if (!(*cmds = add_to_command_list(*cmds, *new_cmd, 1)))
				return (1);
		ft_lstdel(new_cmd, ft_lstdelcontent);
	}
	else if (*arg == '<' || *arg == '>')
		ft_lstadd(new_cmd, ft_lstnew(arg, ft_strlen(arg)));
	else if (arg_is_fd_redirector(arg))
		ft_lstadd(new_cmd, ft_lstnew(arg, ft_strlen(arg)));
	else
	{
		if (ft_isquote(*arg))
			arg = remove_char(arg, *arg);
		ft_lstaddend(new_cmd, ft_lstnew(arg, ft_strlen(arg)));
	}
	return (0);
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
		if (process_argument(cur->content, &cmds, &new_cmd))
			return (NULL);
		cur = cur->next;
	}
	if (ft_lstlen(&new_cmd))
		if (!(cmds = add_to_command_list(cmds, new_cmd, 0)))
			return (NULL);
	ft_lstdel(&new_cmd, ft_lstdelcontent);
	ft_lstdel(&args, ft_lstdelcontent);
	return (cmds);
}
