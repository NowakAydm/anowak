/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/29 19:02:25 by anowak            #+#    #+#             */
/*   Updated: 2015/10/29 19:08:10 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	redirect_from_heredoc(t_cmd *cmd)
{
	t_list	*tmp;

	pipe(cmd->heredoc_pipe);
	if (cmd->fd_in)
		dup2(cmd->fd_in, cmd->heredoc_pipe[0]);
	else
		cmd->fd_in = cmd->heredoc_pipe[0];
	tmp = cmd->heredoc_list;
	while (tmp)
	{
		write(cmd->heredoc_pipe[1], tmp->content, ft_strlen(tmp->content));
		write(cmd->heredoc_pipe[1], "\n", 1);
		tmp = tmp->next;
	}
	close(cmd->heredoc_pipe[1]);
}

int		redirect_input(t_cmd *cmd)
{
	int		ret;
	char	*str;

	ret = 1;
	str = NULL;
	cmd->fd_in = 0;
	if (cmd->input_file)
	{
		cmd->fd_in = open(cmd->input_file, O_RDONLY);
		if (cmd->fd_in == -1)
		{
			ft_putstr_fd("Error : can't open file : ", 2);
			ft_putendl_fd(cmd->input_file, 2);
			return (-1);
		}
	}
	if (cmd->heredoc)
		redirect_from_heredoc(cmd);
	return (0);
}

int		redirect_appending_output(char *str)
{
	int	fd;

	fd = open(str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("Error : can't write output to end of file : ", 2);
		ft_putendl_fd(str, 2);
	}
	return (fd);
}

int		redirect_output(t_cmd *cmd)
{
	int		fd;
	char	*str;

	if (!cmd->out && !cmd->out_append)
		return (0);
	if (cmd->out)
	{
		str = (cmd->out)->content;
		fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			ft_putstr_fd("Error : can't write output to file : ", 2);
			ft_putendl_fd(str, 2);
		}
		ft_lstdel(&cmd->out, ft_lstdelcontent);
	}
	else
	{
		fd = redirect_appending_output((cmd->out_append)->content);
		ft_lstdel(&cmd->out_append, ft_lstdelcontent);
	}
	cmd->fd_out = fd;
	return (0);
}

void	redirect_fd(t_cmd *cmd)
{
	t_list	*tmp;

	tmp = cmd->to_redirect;
	while (tmp)
	{
		if (cmd->out || cmd->out_append || cmd->piped_to)
		{
			ft_putendl_fd("Error : cannot redirect output", 2);
			break ;
		}
		dup2(*((char*)(tmp->content) + 3) - 48, (*(char*)tmp->content - 48));
		tmp = tmp->next;
		if (tmp)
			tmp = tmp->next;
	}
	tmp = cmd->to_close;
	while (tmp)
	{
		close((*(char*)tmp->content) - 48);
		tmp = tmp->next;
	}
}
