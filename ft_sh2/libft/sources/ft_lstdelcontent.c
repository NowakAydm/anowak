/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelcontent.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/19 17:05:39 by anowak            #+#    #+#             */
/*   Updated: 2015/07/14 14:05:40 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelcontent(void *content, size_t content_size)
{
	if (content)
	{
		free(content);
		content = NULL;
	}
	if (content_size)
		content_size = 0;
}
