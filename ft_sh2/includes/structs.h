/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/14 20:50:55 by anowak            #+#    #+#             */
/*   Updated: 2015/09/15 12:59:41 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct	s_ftsh
{
	char	*prompt;
	char	**path_dir;
	char	**env_dup;
	char	*line;
	int		argc;
	char	**argv;
	int		ret;
}				t_ftsh;

typedef struct	s_cmd
{
	char		*path;
	int			argc;
	char		**argv;
	pid_t		pid;
	int			status;
	int			pipeout;
	int			pipein;
	int			fd_in;
	int			fd_out;
}				t_cmd;

#endif
