/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/26 16:27:32 by anowak            #+#    #+#             */
/*   Updated: 2015/10/30 14:38:46 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static int	change_env_oldpwd(char ***envp)
{
	int		x;
	char	*oldpwd;
	char	*pwd;

	x = 0;
	pwd = get_in_env(*envp, "PWD");
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

int			change_env_pwd(char ***envp)
{
	int		x;
	char	*cwd;
	char	*newpwd;

	x = 0;
	cwd = NULL;
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

static char	*get_destination(char **av, char ***envp)
{
	int		len;
	char	*path;

	len = ft_tablen(av);
	path = NULL;
	if (len == 1)
	{
		if (!(path = get_in_env(*envp, "HOME")))
			ft_putendl_fd("Error : could'nt find HOME", 2);
	}
	else if (len == 2)
	{
		if (!strcmp(av[1], "-"))
		{
			if (!(path = get_in_env(*envp, "OLDPWD")))
				ft_putendl_fd("Error : could'nt find OLDPWD", 2);
		}
		else
			path = av[1];
	}
	else
		ft_putendl_fd("Error : too many arguments", 2);
	return (path);
}

int			builtin_cd(char **av, char ***envp)
{
	char	*path;

	if (!(get_in_env(*envp, "PWD")))
		change_env_pwd(envp);
	path = get_destination(av, envp);
	if (path)
	{
		if (chdir(path))
		{
			ft_putstr_fd("Error : can't change to this directory : ", 2);
			ft_putendl_fd(path, 2);
			return (1);
		}
		else
		{
			change_env_oldpwd(envp);
			change_env_pwd(envp);
		}
	}
	else
		return (1);
	return (0);
}
