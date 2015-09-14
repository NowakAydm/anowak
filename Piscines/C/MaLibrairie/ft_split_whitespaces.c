/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/08 17:20:54 by anowak            #+#    #+#             */
/*   Updated: 2014/09/08 23:06:03 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft.h"

int		is_space(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	return (0);
}

int		count_words(char *str)
{
	int	i;
	int	nb;

	nb = 0;
	i = 0;
	while (str[i] != 0)
	{
		while (str[i] != 0 && is_space(str[i]))
			i = i + 1;
		if (str[i] != 0 && !is_space(str[i]))
		{
			nb = nb + 1;
			while (str[i] != 0 && !is_space(str[i]))
				i = i + 1;
		}
	}
	return (nb);
}

char	*word_dup(char *str)
{
	char*ptr;
	int	length;
	int	i;

	length = 0;
	while (str[length] != 0 && !is_space(str[length]))
		length++;
	ptr = malloc(length + 1);
	if (ptr == 0)
		return (0);
	i = 0;
	while (i < length)
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}

char	*extract_word(int word, char *str)
{
	int	i;
	int	nb;

	nb = 0;
	i = 0;
	while (str[i] != 0)
	{
		while (str[i] != 0 && is_space(str[i]))
			i++;
		if (str[i] != 0 && !is_space(str[i]))
		{
			if (nb == word)
				return (word_dup(str + i));
			nb++;
			while (str[i] != 0 && !is_space(str[i]))
				i++;
		}
	}
	return (0);
}

char	**ft_split_whitespaces(char *str)
{
	char**ptr;
	int	nb_words;
	int	i;

	nb_words = count_words(str);
	ptr = malloc(sizeof(char *) * (nb_words + 1));
	if (ptr == 0)
		return (0);
	i = 0;
	while (i < nb_words)
	{
		ptr[i] = extract_word(i, str);
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}
