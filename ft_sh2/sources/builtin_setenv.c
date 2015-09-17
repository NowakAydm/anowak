/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/26 16:30:35 by anowak            #+#    #+#             */
/*   Updated: 2015/09/17 18:39:23 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int			check_if_in_env(char *av, char **env)
{
	int		x;
	char	*var_name;

	x = 0;
	while (env[x])
	{
		if (!(var_name = ft_strcdup(env[x], '=')))
			return (-1);
		if ((ft_strcmp(var_name, av)) == -61)
		{
			free(var_name);
			return (x);
		}
		free(var_name);
		x++;
	}
	return (-1);
}

static char	*change_into_number(char *av)
{
	char	*var_name;
	int		number;

	if (!(var_name = ft_strcdup(av, '=')))
		return (av);
	if (!(ft_strcmp(var_name, "SHLVL")))
	{
		if (!(number = ft_atoi(ft_strchr(av, '=') + 1)))
		{
			free(var_name);
			free(av);
			ft_putendl_fd("Error : SHLVL must be a number", 2);
			return (NULL);
		}
	}
	free(var_name);
	return (av);
}

static int	add_variable_to_env(char *av, char ***env)
{
	char	**new_env;
	int		len;
	int		x;

	x = 0;
	len = ft_tablen(*env);
	if (!(new_env = (char**)ft_memalloc(sizeof(char*) * (len + 2))))
		return (-1);
	while ((*env)[x])
	{
		new_env[x] = ft_strdup((*env)[x]);
		x++;
	}
	new_env[x] = ft_strdup(av);
	ft_tabfree(*env);
	*env = new_env;
	return (0);
}

int			builtin_setenv(char **av, char ***env)
{
	int		x;
	int		ret;

	x = 0;
	ret = 0;
	if (ft_tablen(av) == 1)
	{
		ft_putendl_fd("Error : not enough arguments to setenv", 2);
		return (1);
	}
	while (av[++x])
		if (ft_strchr(av[x], '=') && *(ft_strchr(av[x], '=') + 1)
			&& (av[x] = change_into_number(av[x]))
			&& av[x][0] && av[x][0] != '=')
		{
			if ((ret = check_if_in_env(av[x], *env)) >= 0)
			{
				free((*env)[ret]);
				(*env)[ret] = ft_strdup(av[x]);
			}
			else if ((add_variable_to_env(av[x], env)) == -1)
			{
				ft_putendl_fd("Error : could'nt allocate enough memory", 2);
				return (1);
			}
		}
	return (0);
}
