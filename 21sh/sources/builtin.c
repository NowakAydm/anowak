/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/26 16:31:30 by anowak            #+#    #+#             */
/*   Updated: 2015/10/29 16:06:00 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	execute_builtin(t_cmd *cmd, char ***envp)
{
	if (!(ft_strcmp("cd", cmd->argv[0])))
		return (builtin_cd(cmd->argv, envp) + 1);
	else if (!(ft_strcmp("setenv", cmd->argv[0])))
		return (builtin_setenv(cmd->argv, envp) + 1);
	else if (!(ft_strcmp("unsetenv", cmd->argv[0])))
		return (builtin_unsetenv(cmd->argv, envp) + 1);
	else if (!(ft_strcmp("env", cmd->argv[0])))
		return (builtin_env(*envp) + 1);
	else if (!(ft_strcmp("exit", cmd->argv[0])))
		return (builtin_exit(cmd->argc, cmd->argv) + 1);
	else if (!(ft_strcmp("pid", cmd->argv[0])))
	{
		ft_putstr("Current pid is ");
		ft_putnbr(getpid());
		ft_putendl("");
		return (1);
	}
	return (0);
}

int	check_builtin(t_cmd *cmd)
{
	if (!(ft_strcmp("cd", cmd->argv[0]))
		|| !(ft_strcmp("setenv", cmd->argv[0]))
		|| !(ft_strcmp("unsetenv", cmd->argv[0]))
		|| !(ft_strcmp("env", cmd->argv[0]))
		|| !(ft_strcmp("exit", cmd->argv[0]))
		|| !(ft_strcmp("pid", cmd->argv[0])))
	{
		return (1);
	}
	return (0);
}
