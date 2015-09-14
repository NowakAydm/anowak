/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/16 16:47:32 by anowak            #+#    #+#             */
/*   Updated: 2015/03/16 04:04:16 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <stddef.h>
# include <stdint.h>
# include "libftprintf_struct.h"

# ifndef LIBFT_H

#  include <string.h>

typedef unsigned long long t_ulonglong;

/*
**		Fonctions obligatoires
*/

void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memccpy(void *dst, const void *src, int c, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *s1);
char		*ft_strcpy(char *dst, const char *src);
char		*ft_strncpy(char *dst, const char *src, size_t n);
char		*ft_strcat(char *s1, const char *s2);
char		*ft_strncat(char *s1, const char *s2, size_t n);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strstr(const char *s1, const char *s2);
char		*ft_strnstr(const char *s1, const char *s2, size_t n);
int			ft_strcmp(const char *s1, const char *s);
int			ft_strncmp(const char *s1, const char *s, size_t n);
int			ft_atoi(const char *str);
double		ft_atod(const char *str);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_toupper(int c);
int			ft_tolower(int c);

/*
**		Fonctions supplementaires
*/

void		*ft_memalloc(size_t size);
void		ft_memdel(void **ap);
char		*ft_strnew(size_t n);
void		ft_strdel(char **as);
void		ft_strclr(char *s);
void		ft_striter(char *s, void (*f)(char *));
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
char		*ft_strmap(char const *s, char (*f)(char));
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int			ft_strequ(char const *s1, char const *s2);
int			ft_strnequ(char const *s1, char const *s2, size_t n);
char		*ft_strsub(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s);
char		**ft_strsplit(char const *s, char c);
char		*ft_itoa(int n);
char		*ft_ltoa(long long n);
void		ft_putchar(char c);
void		ft_putstr(char const *s);
void		ft_putendl(char const *s);
void		ft_putnbr(int x);
void		ft_putnbrendl(int x);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char const *s, int fd);
void		ft_putendl_fd(char const *s, int fd);
void		ft_putnbr_fd(int x, int fd);

/*
**		Fonctions liste
*/

t_list		*ft_lstnew(void const *content, size_t content_size);
void		ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void		ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void		ft_lstdelcontent(void *content, size_t content_size);
void		ft_lstadd(t_list **alst, t_list *new);
void		ft_lstaddend(t_list **alst, t_list *new);
void		ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list		*ft_lstsplit(char const *s, char c, int keepc);
void		ft_putlst_str(t_list **alst);
char		*ft_lsttostr(t_list **alst);

/*
**		Fonctions btree
*/

t_btree		*ft_btree_new(void *item);
void		ft_btree_prefix(t_btree *root, void (*applyf)(void*));
void		ft_btree_infix(t_btree *root, void (*applyf)(void*));
void		ft_btree_rev_infix(t_btree *root, void (*applyf)(void*));
void		ft_btree_suffix(t_btree *root, void (*applyf)(void*));
void		ft_btree_insert(t_btree **root, void *item, int (*c)(void*, void*));
void		ft_btree_free(t_btree *root);

/*
**		Fonctions perso
*/

size_t		ft_strlcpy(char *dst, const char *src, size_t size);
char		*ft_strndup(const char *s1, size_t n);
int			ft_count_words(char *s, char c);
int			ft_nbrlen(int n);
char		*ft_strrev(char *s);
int			ft_isspace(int c);
double		ft_puiss10(int c);

# endif

/*
**		Fonctions printf
*/

int			ft_printf(const char *restrict format, ...);

int			get_arg(t_conv *c, t_pf *pf);
t_conv		*convert_type(t_conv *c);
int			add_conv(const char *restrict format, t_pf *pf);
int			scan_format(const char *restrict format, t_pf *pf);

int			set_options(const char *restrict format, t_conv *new);
int			set_width(const char *restrict format, t_conv *new, t_pf *pf);
int			set_long_size(const char *restrict format, t_conv *new);
int			set_size(const char *restrict format, t_conv *new);
int			set_type(const char *restrict format, t_conv *new);

int			set_precision_wild(t_conv *new, t_pf *pf);
int			set_precision(const char *restrict format, t_conv *new, t_pf *pf);

char		*convert_uint(t_conv *c, int base);
char		*convert_int(t_conv *c, int base);
int			print_int_process(t_conv *c, int len, char *str, int x);
int			print_int(t_conv *c);

int			print_char(t_conv *c);
int			print_wide_char(t_conv *c);
int			print_string(t_conv *c);
int			print_long_string_precision(t_conv *c, int len, int w);
int			print_long_string(t_conv *c);

int			print_percent(t_conv *c);
int			print_conv(t_conv *c);
int			print_next_conv(t_pf *pf);
int			print_format(const char *restrict format, t_pf *pf);

void		sharp_hexa(t_conv *c, int len, char *s);
void		sharp_octal(t_conv *c, char *s);
int			sharp(t_conv *c, int len);
int			space_plus(t_conv *c);
int			convert_precision(t_conv *c, int len);

int			put_width(t_conv *c, int len);
int			put_precision(t_conv *c, int len);
int			width_num_process(t_conv *c, int len, int flagneg);
int			width_num(t_conv *c, int len, int flagneg);
int			width_str(t_conv *c, int len);

t_ulonglong	ft_abs(long long n);
char		*ft_ltoa_base(long long n, long long base);
char		*ft_ultoa_base(unsigned long long n, long long base);
wchar_t		*ft_wstrdup(const wchar_t *s1);
size_t		ft_wcharlen(const wchar_t *s);
size_t		ft_wstrlen(const wchar_t *s);
int			ft_putwchar(const wchar_t *c);
int			ft_putwstr(const wchar_t *s);
int			ft_atoi_neg(const char *str);
int			ft_btoi(const char *s);
double		ft_puiss(int n, int puiss);

#endif
