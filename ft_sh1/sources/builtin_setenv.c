/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/26 16:30:35 by anowak            #+#    #+#             */
/*   Updated: 2015/06/11 19:05:19 by anowak           ###   ########.fr       */
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
		if ((ft_strcmp(var_name, av)) == -61)
		{
			printf("---- Found it, returning %d\n", x);
			free(var_name);
			return (x);
		}
		printf("----  Nope : diff = %d\n", ft_strcmp(var_name, av));
		x++;
	}
	return (-1);
}

static int	add_variable_to_env(char *av, char ***env)
{
	char	**new_env = NULL;
	int		len;
	int		x = 0;

	printf(">>>> ADD VAR TO ENV\n");
	len = ft_tablen(*env);
	printf("---- tablen = %d\n", len);
	if (!(new_env = (char**)ft_memalloc(sizeof(char*) * (len + 2))))
		return (-1);
	while ((*env)[x])
	{
		new_env[x] = ft_strdup((*env)[x]);
		printf("---- Adding variable to env | '%s'\n", new_env[x]);
		x++;
	}
	new_env[x] = ft_strdup(av);
	printf("---- Adding NEW variable to env | '%s'\n", new_env[x]);
	ft_tabfree(*env);
	*env = new_env;
	printf("---- env = new_env\n");
	printf("<<<< ADD VAR TO ENV returns 0\n");
	return (0);
}

int			builtin_setenv(char **av, char ***env)
{
	int		x = 1;
	int		ret = 0;

  printf(">>>> Starting BUILTIN - SETENV\n");	
	if (ft_tablen(av) == 1)
	{
		ft_putendl("<<<< Error : not enough arguments to setenv");
		return (0);
	}
	while (av[x])
	{
		if (ft_strchr(av[x], '='))
		{
			if ((ret = check_existing(av[x], *env)) > 0)
			{
				free((*env)[ret]);
				(*env)[ret] = ft_strdup(av[x]);
				printf("---- replaced env[%d] = '%s'\n", ret, (*env)[ret]);
			}
			else
				if ((add_variable_to_env(av[x], env)) == -1)
				{
					printf("<<<< ERROR : add_var_to_env returned -1\n");
					return (-1);
				}
		}
		x++;
	}
	printf("<<<< SETENV returns 1\n");
	return (1);
}
