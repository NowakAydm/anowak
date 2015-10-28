/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/16 17:01:46 by anowak            #+#    #+#             */
/*   Updated: 2015/10/28 16:12:46 by AdamNowak        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	*get_in_env(char **envp, char *var)
{
	int		x;

	x = 0;
	while (envp[x] && ft_strcmp(var, envp[x]) != -61)
		x++;
	if (!(envp[x]))
		return (NULL);
	return (ft_strchr(envp[x], '=') + 1);
}

char	**extract_path_directories(char **envp)
{
	int		x;

	x = 0;
	while (envp[x] && ft_strcmp("PATH", envp[x]) != -61)
		x++;
	if (!(envp[x]))
		return (NULL);
	return (ft_strsplit((ft_strchr(envp[x], '=') + 1), ':'));
}

void	increment_shlvl(char ***env)
{
	int		n;
	char	**str;
	
	if (get_in_env(*env, "SHLVL"))
	{
		n = ft_atoi(get_in_env(*env, "SHLVL"));
		str = ft_memalloc(sizeof(char*) * 3);
		str[0] = ft_strdup("setenv");
		str[1] = ft_strnew(20);
		str[1] = ft_strcat(str[1], "SHLVL=");
		str[1] = ft_strcat(str[1], ft_itoa(++n));
		builtin_setenv(str, env);
		ft_tabfree(str);
	}
}

t_ftsh	*intialize_sh(int argc, char **argv, char **envp)
{
	t_ftsh	*sh;

	sh = NULL;
	sh = ft_memalloc(sizeof(t_ftsh));
	if (sh)
	{
		if (initialize_term(sh, envp) == -1)
			return (NULL);
		sh->prompt = ft_strdup(PROMPT);
		if (!(sh->prompt))
			return (NULL);
		sh->env_dup = ft_tabdup(envp);
		increment_shlvl(&(sh->env_dup));
		sh->line = NULL;
		change_env_pwd(&(sh->env_dup));
		if (sh->env_dup)
			sh->path_dir = extract_path_directories(sh->env_dup);
		sh->argc = argc;
		sh->argv = argv;
	}
	else
		return (NULL);
	return (sh);
}

int		main(int argc, char **argv, char **envp)
{
	t_ftsh	*sh;

	ft_putendl("____----    FT_MINISHELL2    ----____");
	sh = NULL;
	sh = intialize_sh(argc, argv, envp);
	if (!sh)
	{
		ft_putendl_fd("Error : could'nt initialize shell", 2);
		return (1);
	}
	while (1)
	{
		catch_signals();
		if (sh->line)
			free(sh->line);
		sh->line = NULL;
		write(1, sh->prompt, ft_strlen(sh->prompt));
		if ((sh->line = get_command_line()) != NULL)
		{
			sh->ret = execute_command_line(sh, &(sh->env_dup));
			ft_tabfree(sh->path_dir);
			sh->path_dir = extract_path_directories(sh->env_dup);
		}
		else
		{
			restore_term(NULL);
			exit(1);
		}
	}
}
