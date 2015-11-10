/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/29 19:04:27 by anowak            #+#    #+#             */
/*   Updated: 2015/10/29 19:06:12 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	print_input_redirection_error(t_cmd *cmd)
{
	ft_putstr_fd("Error : ", 2);
	ft_putstr_fd(cmd->argv[0], 2);
	if (cmd->input_file)
	{
		ft_putstr_fd(" < ", 2);
		ft_putstr_fd(cmd->input_file, 2);
	}
	else
	{
		ft_putstr_fd(" << ", 2);
		ft_putstr_fd(cmd->heredoc, 2);
	}
	ft_putendl_fd(" : can't redirect input of a piped command", 2);
}

void	print_ret_message(int status, char *cmd)
{
	if (status && status <= 31 && status > 0)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(" : ", 2);
		ft_putnbr_fd(status, 2);
		ft_putstr_fd(" : ", 2);
		if (status == SIGINT)
			ft_putendl_fd("process interrupted", 2);
		else if (status == SIGQUIT)
			ft_putendl_fd("process aborted", 2);
		else if (status == SIGSTOP || status == SIGTSTP)
			ft_putendl_fd("process stopped", 2);
		else if (status == SIGKILL)
			ft_putendl_fd("kill program", 2);
		else if (status == SIGBUS)
			ft_putendl_fd("bus error", 2);
		else if (status == SIGSEGV)
			ft_putendl_fd("segmentation fault", 2);
		else if (status == SIGSYS)
			ft_putendl_fd("unknown system call", 2);
		else if (status == SIGILL)
			ft_putendl_fd("illegal instruction", 2);
		else
			ft_putendl_fd("something bad happened", 2);
	}
}
