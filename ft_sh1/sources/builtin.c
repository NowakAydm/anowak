/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/26 16:31:30 by anowak            #+#    #+#             */
/*   Updated: 2015/07/12 15:26:19 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	check_builtin(t_cmd *cmd, char ***envp)
{
	if (!(ft_strcmp("cd", cmd->argv[0])))
	{
		builtin_cd(cmd->argv, envp);
		return (1); 
	}
	else if (!(ft_strcmp("setenv", cmd->argv[0])))
	{
		builtin_setenv(cmd->argv, envp);
		return (1); 
	}
	else if (!(ft_strcmp("unsetenv", cmd->argv[0])))
	{
		builtin_unsetenv(cmd->argv, envp);
		return (1); 
	}
	else if (!(ft_strcmp("env", cmd->argv[0])))
	{
		builtin_env(cmd->argv, *envp);
		return (1); 
	}
	else if (!(ft_strcmp("exit", cmd->argv[0])))
	{
		exit(0);
		return (1); 
	}
	else
		return (0);
}
