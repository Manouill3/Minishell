/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:10:23 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/27 16:27:53 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdint.h>

typedef struct s_mal
{
	void			*content;
	struct s_mal	*next;
}			t_mal;

typedef struct s_list
{
	int				content;
	struct s_list	*next;
}	t_list;

uint8_t		ft_atoi(const char *nptr);
void		ft_bzero(void *s, size_t n);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memset(void *s, int c, size_t n);
char		*ft_strchr(const char *s, int c);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_strrchr(const char*s, int c);
int			ft_tolower(int c);
int			ft_toupper(int c);
void		*ft_calloc(size_t nmemb, size_t size);
char		*ft_strdup(const char *s, t_mal *mal);
char		*ft_substr(char const *s, unsigned int start,
				size_t len, t_mal *mal);
char		*ft_itoa(int n, t_mal *mal);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
char		*ft_strjoin(char const *s1, char const *s2, t_mal *mal);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, t_mal *mal);
t_list		*ft_lstnew(int content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst);
void		ft_lstclear(t_list **lst);
void		ft_lstiter(t_list *lst, void (*f)(int));
t_list		*ft_lstmap(t_list *lst, int (*f)(int));
int			get_quote(int i, const char *s, char c);
int			secu(int k, char const *s);
char		**exec_all(const char *s, int k, t_mal *mal, char **tab);
int			len_word(const char *s, int start);
void		free_all(char	**tab);
int			len_first_tab(const char *s);
int			is_white(char c);
int			is_ope(char c);
char		**ft_normal_split(char const *s, char c, t_mal *mal);
char		*handle_quote(const char *s, int *k, char *tab, t_mal *mal);
char		*ft_extract_word(const char *s, int *k, char *tab, t_mal *mal);
char		**split_ope(const char *s, int k, char **tab, t_mal *mal);

t_mal		*ft_lstnew_mal(void *str);
void		ft_lstadd_back_mal(t_mal **lst, t_mal *new);
void		ft_lstclear_mal(t_mal **lst);
void		ft_lstdelone_mal(t_mal *lst);
void		*add_malloc(t_mal *mal, size_t size);
void		*add_calloc(t_mal *mal, size_t size, size_t sizeb);

#endif
