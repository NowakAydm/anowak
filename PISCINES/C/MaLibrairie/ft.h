/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/08 14:46:56 by anowak            #+#    #+#             */
/*   Updated: 2014/09/08 21:22:09 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		FT_H
# define	FT_H

/*
**__________ ft_put(stuff) __________
*/
void	ft_putchar(char c);
void	ft_putstr(char *str);
void	ft_putnbr(int nbr);

/*
**__________ ft_(numbers)  __________
*/
int		ft_atoi(char *str);
int		ft_puiss10(int y);
int		ft_iterative_factorial(int nb);
int		ft_recursive_factorial(int nb);
int		ft_iterative_power(int nb, int power);
int		ft_recursive_power(int nb, int power);
int		ft_sqrt(int nb);

/*
**__________ ft_str(stuff) __________
*/
char	*ft_strcpy(char *dest, char *src);
char	*ft_strncpy(char *dest, char *src, unsigned int n);
char	*ft_strdup(char *src);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
int		ft_strlen(char *str);

char	*ft_strupcase(char *str);
char	*ft_strlowcase(char *str);

char	**ft_split_whitespaces(char *str);

/*
**__________ ft_str(checks) __________
*/
int		ft_str_is_alpha(char *str);
int		ft_str_is_lowercase(char *str);
int		ft_str_is_uppercase(char *str);
int		ft_str_is_numeric(char *str);
int		ft_str_is_printable(char *str);

#endif
