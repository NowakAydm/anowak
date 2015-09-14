/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libfts.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/14 17:30:26 by anowak            #+#    #+#             */
/*   Updated: 2015/04/14 17:37:41 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTS_H
# define LIBFTS_H

void	ft_bzero(void *s, size_t n);
char	*ft_strcat(char *restrict s1, const char *restrict s2);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_puts(char *s);

int		ft_strlen(char *s);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n);
char	*ft_strdup(char *s);

void	ft_cat(int fd);

int		ft_islower(int c);
int		ft_isupper(int c);
int		ft_putstr(char *s);
char	*ft_strncat(char *restrict s1, const char *restrict s2, size_t n);
char	*ft_strnew(size_t n);

#endif
