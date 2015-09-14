/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/26 19:31:37 by anowak            #+#    #+#             */
/*   Updated: 2015/07/12 15:21:47 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static int	check_existing(char *av, char **env)
{
	int		x = 0;
	char	*var_name = NULL;

	printf("---- checking if new var already exists\n");
	while (env[x])
	{
		if (!(var_name = ft_strcdup(env[x], '=')))
			return (-1);
		printf("---- Checking '%s'\n", var_name);
		if (!(ft_strcmp(var_name, av)))
		{
			printf("---- Found it, returning %d\n", x);
			free(var_name);
			return (x);
		}
		printf("----  Nope : diff = %d\n", ft_strcmp(var_name, av));
		x++;
	}
	return (-2);
}

static int	sub_variable_to_env(char ***env, int pos)
{
	char	**new_env = NULL;
	int		len;
	int		x = 0;
	int		y = 0;

	printf(">>>> SUB VAR TO ENV\n");
	len = ft_tablen(*env);
	printf("---- tablen = %d\n", len);
	if (!(new_env = (char**)ft_memalloc(sizeof(char*) * (len))))
		return (-1);
	while ((*env)[x])
	{
		if (x == pos)
			printf("---- Skipping variable | '%s'\n", (*env)[x]);
		else
		{
			new_env[y] = ft_strdup((*env)[x]);
			printf("---- Adding variable to env | '%s'\n", new_env[y]);
			y++;
		}
		x++;
	}
	ft_tabfree(*env);
	*env = new_env;
	printf("---- env = new_env\n");
	printf("<<<< SUB VAR TO ENV returns 0\n");
	return (0);	
}

int			builtin_unsetenv(char **av, char ***env)
{
	int	ret = 0;
	int	x = 1;

	printf(">>>> Starting BUILTIN - UNSETENV\n");	
	
	if (ft_tablen(av) == 1)
	{
		ft_putendl("<<<< Error : not enough arguments to unsetenv");
		return (0);
	}
	while (av[x])
	{
		if ((ret = check_existing(av[x], *env)) >= 0)
		{
			if ((sub_variable_to_env(env, ret)) == -1)
				return (-1);
		}
		else if (ret == -1)
			return (-1);
		x++;
	}
	printf("<<<< UNSETENV returns 1\n");
	return (1);
}
