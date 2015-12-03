/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/29 16:18:11 by anowak            #+#    #+#             */
/*   Updated: 2015/11/10 18:15:59 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

t_list	*process_redirection(t_list *args, t_cmd *cmd)
{
	while (*(char*)(args->content) == '<' || *(char*)(args->content) == '>'
			|| arg_is_fd_redirector((char*)(args->content)))
	{
		if (!cmd->input_file && !cmd->heredoc)
			add_input_redirection(cmd, args->content);
		if (!cmd->out_append && !cmd->out)
			add_output_redirection(cmd, args->content);
		if (arg_is_fd_redirector((char*)(args->content)))
			add_output_redirection(cmd, args->content);
		if (!(args = args->next))
			return (NULL);
	}
	return (args);
}

int		get_heredoc(t_cmd *cmd)
{
	char	*line;
	int		ret;
	int		len;

	line = NULL;
	ret = 1;
	if (signal(SIGINT, process_terminate_in_process) == SIG_ERR)
		ft_putendl_fd("Error : can't catch signal", 2);
	while (ft_strcmp(line, cmd->heredoc) != 0)
	{
		ft_putstr("heredoc ('");
		ft_putstr(cmd->heredoc);
		ft_putstr("') > ");
		ret = read_next_line(&line);
		len = ft_strlen(line);
		if (ret == -1)
			return (-1);
		printf("STRCMP - %s - %s == %d\n", line, cmd->heredoc, ft_strcmp(line, cmd->heredoc));
		if (ft_strcmp(line, cmd->heredoc) != 0)
			ft_lstaddend(&(cmd->heredoc_list), ft_lstnew(line, len));
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
	int		x;
	char	*s;

	x = 1;
	if (ft_strcmp(arg, ">") == '>')
	{
		x++;
		while (ft_isspace(arg[x]))
			x++;
		s = (char*)(arg + x);
		if (arg[x])
			ft_lstadd(&cmd->out_append, ft_lstnew(s, ft_strlen(s)));
	}
	else if (ft_isdigit(*arg) && ft_strcmp(arg + 1, ">&") == '-')
		ft_lstadd(&cmd->to_close, ft_lstnew((char*)arg, 1));
	else if (ft_isdigit(*arg) && ft_isdigit(ft_strcmp(arg + 1, ">&")))
		ft_lstadd(&cmd->to_redirect, ft_lstnew((char*)arg, 4));
	else if (*arg == '>')
	{
		while (ft_isspace(arg[x]))
			x++;
		s = (char*)(arg + x);
		if (arg[x])
			ft_lstadd(&cmd->out, ft_lstnew(s, ft_strlen(s)));
	}
}

int		arg_is_fd_redirector(char *arg)
{
	int x;

	x = 0;
	if (!arg)
		return (0);
	while (ft_isspace(arg[x]))
		x++;
	if (ft_isdigit(arg[x]))
		x++;
	if (x && ft_strcmp(arg + 1, ">&") == '-')
		return (1);
	if (x && ft_isdigit(ft_strcmp(arg + 1, ">&")))
		return (1);
	return (0);
}
