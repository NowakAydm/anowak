/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/29 17:10:08 by anowak            #+#    #+#             */
/*   Updated: 2016/01/22 20:10:10 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char		*get_in_env(char **envp, char *var)
{
	int		x;

	x = 0;
	while (envp[x] && ft_strcmp(var, envp[x]) != -61)
		x++;
	if (!(envp[x]))
		return (NULL);
	return (ft_strchr(envp[x], '=') + 1);
}

char		**extract_path_directories(char **envp)
{
	int		x;

	x = 0;
	while (envp[x] && ft_strcmp("PATH", envp[x]) != -61)
		x++;
	if (!(envp[x]))
		return (NULL);
	return (ft_strsplit((ft_strchr(envp[x], '=') + 1), ':'));
}

t_ftsh		*intialize_sh(int argc, char **argv, char **envp)
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

void		command_line_loop(t_ftsh *sh)
{
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

int			main(int argc, char **argv, char **envp)
{
	t_ftsh	*sh;

	sh = NULL;
	sh = intialize_sh(argc, argv, envp);
	if (!sh)
	{
		ft_putendl_fd("Error : could'nt initialize shell", 2);
		exit(1);
	}
	while (1)
	{
		catch_signals();
		if (sh->line)
			free(sh->line);
		sh->line = NULL;
		write_prompt(&(sh->prompt));
		command_line_loop(sh);
	}
}
