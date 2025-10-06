/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:04:56 by jose-cad          #+#    #+#             */
/*   Updated: 2025/09/04 14:05:00 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef GNL_SIZE
#  define GNL_SIZE 42
# endif

# include "../src/printf/ft_printf.h"
# include <unistd.h>
# include <stdlib.h>

int				ft_atoi(const char *nptr);
int				ft_atoi_base(const char *str, const char *base);
unsigned int	ft_ato_bin(const char *str);
unsigned int	ft_ato_octa(const char *str);
unsigned long	ft_atohex_ptr(const char *hex_str);
unsigned int	ft_atohex(const char *str);
double			ft_atof(const char *str);
long			ft_atol(const char *nptr);
int				ft_base_is_valid(const char *base);
char			*ft_bin_toa(unsigned int nbr);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t nmemb, size_t size);
size_t			count_digits(unsigned int nbr, size_t base_len);
char			*ft_ftoa(double n, int precision);
unsigned long	ft_hextoa_ptr(const char *hex_str);
char			*ft_hextoa_lower(unsigned int nbr);
char			*ft_hextoa_upper(unsigned int nbr);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
int				ft_isspace(int c);
char			*ft_itoa(int n);
char			*ft_itoa_base(int nbr, char *base);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memset(void *s, int c, size_t n);
char			*ft_octa_toa(unsigned int nbr);
char			*ft_ptr_hextoa(unsigned long ptr);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr_fd(char *s, int fd);
char			**ft_split(char const *s, char c);
char			*ft_strchr(const char *s, int c);
char			*ft_strdup(const char *s);
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlcat(char *dst, const char *src, size_t dsize);
size_t			ft_strlcpy(char *dst, const char *src, size_t dsize);
size_t			ft_strlen(const char *s);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnstr(const char *base, const char *target, size_t len);
char			*ft_strrchr(const char *s, int c);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_substr(char const *s, unsigned int start, size_t len);
int				ft_toupper(int c);
int				ft_tolower(int c);
char			*ft_utoa_base(unsigned int nbr, const char *base);

//list
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstadd_front(t_list **lst, t_list *new);
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));
t_list			*ft_lstnew(void *content);
int				ft_lstsize(t_list *lst);

// dlist
typedef struct s_dlist
{
	void			*content;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}	t_dlist;

t_dlist			*ft_dlstnew(void *content);
void			ft_dlstadd_front(t_dlist **lst, t_dlist *new);
void			ft_dlstadd_back(t_dlist **lst, t_dlist *new);
t_dlist			*ft_dlstlast(t_dlist *lst);
int				ft_dlstsize(t_dlist *lst);
void			ft_dlstdelone(t_dlist *lst, void (*del)(void *));
void			ft_dlstclear(t_dlist **lst, void (*del)(void *));
void			ft_dlstiter(t_dlist *lst, void (*f)(void *));
t_dlist			*ft_dlstmap(t_dlist *lst, void *(*f)(void *),
					void (*del)(void *));

// gnl
char			*get_next_line(int fd);
void			*gnl_free(void *ptr1, void *ptr2);
size_t			gnl_strlen(const char *s);
char			*gnl_strchr(const char *s, int c);
char			*gnl_strjoin(char *s1, char *s2);

#endif
