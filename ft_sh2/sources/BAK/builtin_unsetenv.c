/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/26 19:31:37 by anowak            #+#    #+#             */
/*   Updated: 2015/07/16 18:51:10 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static int	check_existing(char *av, char **env)
{
	int		x;
	char	*var_name;

	x = 0;
	while (env[x])
	{
		if (!(var_name = ft_strcdup(env[x], '=')))
			return (-1);
		if (!(ft_strcmp(var_name, av)))
		{
			free(var_name);
			return (x);
		}
		free(var_name);
		x++;
	}
	return (-2);
}

static int	sub_variable_to_env(char ***env, int pos)
{
	char	**new_env;
	int		len;
	int		x;
	int		y;

	x = 0;
	y = 0;
	len = ft_tablen(*env);
	if (!(new_env = (char**)ft_memalloc(sizeof(char*) * (len))))
		return (-1);
	while ((*env)[x])
	{
		if (x != pos)
		{
			new_env[y] = ft_strdup((*env)[x]);
			y++;
		}
		x++;
	}
	ft_tabfree(*env);
	*env = new_env;
	return (0);
}

int			builtin_unsetenv(char **av, char ***env)
{
	int	ret;
	int	x;

	ret = 0;
	x = 1;
	if (ft_tablen(av) == 1)
	{
		ft_putendl_fd("Error : not enough arguments to unsetenv", 2);
		return (1);
	}
	while (av[x])
	{
		if ((ret = check_existing(av[x], *env)) >= 0)
		{
			if ((sub_variable_to_env(env, ret)) == -1)
			{
				ft_putendl_fd("Error : could'nt allocate enough memory", 2);
				return (1);
			}
		}
		else if (ret == -1)
			return (1);
		x++;
	}
	return (0);
}
