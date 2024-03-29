/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheo <jiheo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 21:07:08 by jiheo             #+#    #+#             */
/*   Updated: 2022/07/01 17:11:28 by jiheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "unistd.h"
# include "stdio.h"
# include "limits.h"
# include "stdlib.h"
# include "stdbool.h"

typedef struct s_list_node
{
	void				*content;
	struct s_list_node	*next;
	struct s_list_node	*prev;
}	t_list_node;


typedef struct s_list
{
	t_list_node	*front;
	t_list_node	*rear;
	int			len;
}			t_list;

typedef long long		t_ll;
typedef unsigned char	t_uchar;

// Mendatory functions
bool	ft_isalpha(int c);
bool	ft_isdigit(int c);
bool	ft_isalnum(int c);
bool	ft_isascii(int c);
bool	ft_isprint(int c);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, int n);
void	*ft_memcpy(void *__restrict __dst, \
					const void *__restrict __src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
size_t	ft_strlcpy(char *__restrict __dst, \
					const char *__restrict __src, size_t dstsize);
size_t	ft_strlcat(char *__restrict __dst, \
					const char *__restrict __src, size_t dstsize);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);

// Additional functions
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strtrim(const char *s1, char const *set);
char	**ft_split(const char *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

// Bonus functions
t_list_node	*ft_new_node(void *item);
t_list		*ft_lstnew(void);
void		ft_lstadd_front(t_list *lst, void *item);
int			ft_lstsize(t_list *lst);
t_list_node	*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list *lst, void *item);
void		ft_lstclear(t_list *lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));

#endif