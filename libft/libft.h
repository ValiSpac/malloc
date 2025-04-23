/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopayet- <lopayet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:21:44 by vpac              #+#    #+#             */
/*   Updated: 2023/04/29 16:14:06 by lopayet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <limits.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int		ft_isalpha(int str);
int		ft_isalnum(int str);
int		ft_isascii(int str);
int		ft_isprint(int c);
size_t	ft_strlen(const char *str);
int		ft_isdigit(int str);
void	*ft_memset(void *str, int c, size_t n);
void	*ft_memmove(void *str1, const void *str2, size_t n);
void	ft_bzero(void *str, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t n);
size_t	ft_strlcat(char *dst, const char *src, size_t n);
char	*ft_strcat(char *restrict str1, const char *restrict str2);
int		ft_toupper(int str);
char	*ft_strchr(const char *s, int c);
int		ft_tolower(int str);
char	*ft_strrchr(const char *str, int c);
int		ft_strncmp(char *s1, char *s2, size_t n);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strnstr(const char *str1, const char *str2, size_t n);
void	*ft_memchr(const void *str, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strdup(char *src);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_itoa(int n);
char	**ft_split(char const *s, char c);
void	ft_split_free(char **ptr);
int		ft_atoi(const char *str);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char const *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putchar(char c);
void	ft_putstr(char *str);
int		ft_wdcount(char const *str, char c);
char	*ft_strjoin_free(char *s1, char *s2);
int		char_in_set(char c, char const *set);
char	*ft_strndup(const char *s1, size_t n);
size_t	ft_max(size_t x, size_t y);
void	ft_memdel(void **ap);
char	*ft_strcpy(char *dst, const char *src);
void	ft_strclr(char *s);
void	ft_strdel(char **as);
char	*ft_strnew(size_t size);
char	*get_next_line(int fd);
char	*ft_strnchr(const char *s, int c, size_t n);
//list
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void*));
int		ft_lstsize(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
t_list	*ft_lstlast(t_list *lst);
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
