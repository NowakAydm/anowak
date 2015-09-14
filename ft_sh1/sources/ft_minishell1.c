/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/04 19:47:55 by anowak            #+#    #+#             */
/*   Updated: 2015/07/12 16:11:04 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	**extract_path_directories(char **envp)
{	
	int		x = 0;

	while (envp[x] && ft_strcmp("PATH", envp[x]) != -61)
	    x++;
	if (!(envp[x]))
	  return (NULL);
	return (ft_strsplit((ft_strchr(envp[x], '=') + 1), ':'));
}

void		process_sigint(int signal)
{
  printf("Caught Ctrl + C -- signal = %d\n", signal);
  return;
}

int		main(int argc, char **argv, char **envp)
{
	printf("----------------  FT_MINISHELL 1 ----------------\n");
	printf("\\/\\/\\/\\/\\/\\/\\/\\/    by           \\/\\/\\/\\/\\/\\/\\/\\/\n");
	printf("/\\/\\/\\/\\/\\/\\/\\/\\     anowak      /\\/\\/\\/\\/\\/\\/\\/\\\n");
	printf("-------------------------------------------------\n");
	printf("ac = %d\n", argc);
	int x = -1;
	
	while (argv[++x])
		printf("av[%d] = '%s'\n", x, argv[x]);
	x = -1;
	while (envp[++x])
		printf("ap[%d] = '%s'\n", x, envp[x]);
	while (argv[++x])
		printf("\n");

	char	*prompt = NULL;
	char	**path_dir = NULL;
	char	**env_dup = NULL;
	char	*line = NULL;
	
	if (signal(2, process_sigint) == SIG_ERR)
	  {
		printf("Error : can't catch signal\n");	    
	  }

	prompt = ft_strdup(PROMPT);
	env_dup = ft_tabdup(envp);
	path_dir = extract_path_directories(env_dup);
	if (!(path_dir) || !(prompt) || !(env_dup))
	{
		printf("Error : could'nt allocate enough memory\n");
		return (0);
	}
	x = -1;	
	while (path_dir[++x])
		printf("path_dir[%d] = '%s'\n", x, path_dir[x]);

	while (1)
	{
		write(1, prompt, ft_strlen(prompt));
		if ((line = get_command_line()) != NULL)
		{
			execute_command_line(line, path_dir, &env_dup);
			free(line);
			ft_tabfree(path_dir);
			path_dir = extract_path_directories(env_dup);
		} 
		else
			printf("Error : get_command_line RETURNED NULL\n");
		line = NULL;
	}
	free(prompt);
	
	(void)argc;
	(void)argv;
	(void)envp;

	return (0);
}
