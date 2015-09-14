/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/26 16:27:32 by anowak            #+#    #+#             */
/*   Updated: 2015/07/01 00:12:20 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static char	*get_in_env(char **envp, char *var)
{
	int		x = 0;
	
	while (envp[x] && ft_strcmp(var, envp[x]) != -61)
		x++;
	if (!(envp[x]))
		return (NULL);
	return (ft_strchr(envp[x], '=') + 1);
}

static int	change_env_oldpwd(char ***envp, char *pwd)
{	
	int		x = 0;
	char	*oldpwd = NULL;
	
	if (!(oldpwd = ft_strnew(ft_strlen(pwd) + 8)))
		return (-1);
	oldpwd = ft_strncat(oldpwd, "OLDPWD=", 7);
	oldpwd = ft_strncat(oldpwd, pwd, ft_strlen(pwd));

	while ((*envp)[x] && ft_strcmp("OLDPWD", (*envp)[x]) != -61)
		x++;
	if (!((*envp)[x]))
		*envp = ft_tabadd(envp, oldpwd);
	else
	{
		free((*envp)[x]);
		(*envp)[x] = ft_strdup(oldpwd);
	}
	free(oldpwd);
	return (0);
}

static int	change_env_pwd(char ***envp)
{	
	int		x = 0;
	char	*cwd = NULL;
	char	*newpwd = NULL;
	
	if (!(cwd = getcwd(NULL, 1)))
		return (-1);
	if (!(newpwd = ft_strnew(ft_strlen(cwd) + 5)))
		return (-1);
	newpwd = ft_strncat(newpwd, "PWD=", 4);
	newpwd = ft_strncat(newpwd, cwd, ft_strlen(cwd));

	while ((*envp)[x] && ft_strcmp("PWD", (*envp)[x]) != -61)
		x++;
	if (!((*envp)[x]))
		*envp = ft_tabadd(envp, newpwd);
	else
	{
		free((*envp)[x]);
		(*envp)[x] = ft_strdup(newpwd);
	}
	free(cwd);
	free(newpwd);
	return (0);
}

int	builtin_cd(char **av, char ***envp)
{
	int	len = 0;
	
	printf(">>>> Starting BUILTIN - CD\n");
	len = ft_tablen(av);
	printf("---- len av = %d\n", len);
	if (len == 1)
    {
		if (get_in_env(*envp, "HOME"))
		{
			if (chdir(get_in_env(*envp, "HOME")))
			{
				printf("<<<< Error : chdir returned -1\n");
				return (-1);
			}
			else
			{
				change_env_pwd(envp);
				printf("---- Changing to HOME directory : %s\n", get_in_env(*envp, "HOME"));
			}
		}
		else
			printf("<<<< Error : could'nt find HOME\n");
    }
	else if (len == 2)
	{
		if (!strcmp(av[1], "-"))
		{
			printf("---- Changing av[1] into OLDPWD\n");
			av[1] = get_in_env(*envp, "OLDPWD");
		}
		printf("---- Changing to '%s' directory\n", av[1]);
		if (chdir(av[1]))
		{
			printf("<<<< Error : chdir returned -1\n");
			return (-1);
		}
		else
		{
			change_env_oldpwd(envp, get_in_env(*envp, "PWD"));
			change_env_pwd(envp);
		}
	}	
	printf("<<<< CD returns 1\n");
	return (1);
}
