/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/14 17:31:51 by anowak            #+#    #+#             */
/*   Updated: 2016/01/19 15:23:24 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void		process_terminate_in_sh(int signum)
{
	(void)signum;
	ft_putendl("");
	ft_putstr(PROMPT);
	clear_line(NULL);
	return ;
}

void		process_terminate_in_process(int signum)
{
	(void)signum;
	return ;
}

void		process_buserr(int signum)
{
	(void)signum;
	ft_putendl_fd("\nCaught 'Bus Error'", 2);
	restore_term(NULL);
	exit(1);
	return ;
}

void		process_segfault(int signum)
{
	(void)signum;
	ft_putendl_fd("\nCaught 'Segmentation Fault'", 2);
	restore_term(NULL);
	exit(1);
	return ;
}

void		catch_signals(void)
{
	signal(SIGTSTP, SIG_IGN);
	if (signal(SIGHUP, process_terminate_in_sh) == SIG_ERR)
		ft_putendl_fd("Error : can't catch signal", 2);
	if (signal(SIGINT, process_terminate_in_sh) == SIG_ERR)
		ft_putendl_fd("Error : can't catch signal", 2);
	if (signal(SIGSEGV, process_segfault) == SIG_ERR)
		ft_putendl_fd("Error : can't catch signal", 2);
	if (signal(SIGBUS, process_buserr) == SIG_ERR)
		ft_putendl_fd("Error : can't catch signal", 2);
	return ;
}
