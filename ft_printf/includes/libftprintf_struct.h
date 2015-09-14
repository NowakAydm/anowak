/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf_struct.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/16 16:49:13 by anowak            #+#    #+#             */
/*   Updated: 2015/03/13 03:09:57 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_STRUCT_H
# define LIBFTPRINTF_STRUCT_H

# ifndef LIBFT_STRUCT_H

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

# endif

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
