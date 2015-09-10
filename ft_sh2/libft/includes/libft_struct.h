/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/03 19:45:00 by anowak            #+#    #+#             */
/*   Updated: 2015/05/04 19:33:12 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_STRUCT_H
# define LIBFT_STRUCT_H

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_btree
{
	struct s_btree	*left;
	struct s_btree	*right;
	void			*item;
}					t_btree;

typedef struct		s_conv
{
	int				sharp;
	int				zero;
	int				minus;
	int				plus;
	int				space;
	long			width;
	long			precision;
	char			size;
	char			type;
	void			*arg;
	char			**str;
	int				len;
}					t_conv;

typedef struct		s_pf
{
	va_list			ap;
	t_list			*list;
	int				ret;
}					t_pf;

#endif
