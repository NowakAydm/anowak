/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 11:50:17 by anowak            #+#    #+#             */
/*   Updated: 2015/10/30 15:42:27 by anowak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdint.h>
# include "libft_struct.h"

typedef unsigned long long	t_ulonglong;
typedef t_btree				t_bt;

# define BUFF_SIZE 8

/*
**		Fonctions obl igatoires
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
**			Fonctions supplementaires
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
**			Fonctions liste
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
char		**ft_lsttotab(t_list **alst);
char		**ft_lsttotab_n(t_list **alst, int n);
int			ft_lstlen(t_list **alst);

/*
**			Fonctions btree
*/
t_btree		*ft_btree_new(void *item);
void		ft_btree_prefix(t_btree *root, void (*applyf)(void*));
void		ft_btree_infix(t_btree *root, void (*applyf)(void*));
void		ft_btree_rev_infix(t_btree *root, void (*applyf)(void*));
void		ft_btree_suffix(t_btree *root, void (*applyf)(void*));
void		ft_btree_insert(t_bt **root, void *item, int (*cmpf)(void*, void*));
void		ft_btree_free(t_btree *root);

/*
**			Fonctions perso
*/

int			get_next_line_singlefd(int const fd, char **line);
int			get_next_line(int const fd, char **line);

size_t		ft_strlcpy(char *dst, const char *src, size_t size);
char		*ft_strndup(const char *s1, size_t n);
char		*ft_strcdup(const char *s1, char c);
int			ft_count_words(char *s, char c);
int			ft_nbrlen(int n);
char		*ft_strrev(char *s);
int			ft_isspace(int c);
double		ft_puiss10(int c);

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
int			ft_tablen(char **tab);
void		ft_tabfree(char **tab);
char		**ft_tabadd(char ***tab, char *str);
char		**ft_tabdup(char **tab);
int			ft_isquote(int c);
int			ft_isparenthesis(int c);
int			ft_toclosingparenthesis(int c);

#endif
