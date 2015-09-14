/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/26 16:31:07 by anowak            #+#    #+#             */
/*   Updated: 2015/05/26 18:55:09 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	builtin_env(char **av, char **env)
{
  int x = 0;

  (void) av;
  printf(">>>> Starting BUILTIN - ENV\n");
  while (env[x])
    {
      ft_putendl(env[x]);
      x++;
    }
  printf("<<<< ENV returns 1\n");
  return (1);
}
