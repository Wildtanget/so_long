/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notahtah <notahtah@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:27:13 by notahtah          #+#    #+#             */
/*   Updated: 2024/01/15 00:41:33 by notahtah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>

/*--- Node structure ---*/

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;


/*=======================*/
/*--- Basic utilities ---*/
/*=======================*/

/*--- Character comparison ---*/
int		ft_isalnum(int c);
int		ft_isalpha(int arg);
int		ft_isascii(int arg);
int		ft_isdigit(int arg);
int		ft_isprint(int arg);

/*--- String <~~~> Integer ---*/
int		ft_atoi(const char *str);
char	*ft_itoa(int n);

/*--- Utilities for linked lists ---*/
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/*--- Memory manipulation ---*/
void	*ft_memchr(const void *str, int c, size_t n);
int		ft_memcmp(const void *str1, const void *str2, size_t num);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t n);
void	*ft_memset(void *string, int c, size_t n);
void	*ft_bzero(void *string, size_t n);
void	*ft_calloc(size_t nitems, size_t size);

/*--- Write to a file descriptor ---*/
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);

/*--- String manipulation ---*/
char	**ft_split(char const *s1, char c);
char	*ft_strchr(const char *str, int c);
char	*ft_strdup(const char *str1);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *string);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *str1, const char *str2, size_t num);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strrchr(const char *str, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);

int		ft_tolower(int ch);
int		ft_toupper(int ch);	


/*=============================*/
/*--- Printf implementation ---*/
/*=============================*/

int		ft_printf(const char *format, ...);
int		ft_print_specifier(int specifier, va_list args);

/*--- Print a character or string ---*/
int		ft_print_char(int character);
int		ft_print_string(char *string);
int		ft_print_percent(void);

/*--- Print an (unsigned) integer ---*/
int		ft_print_integer(int number);
int		ft_print_unsigned(unsigned int number);

/*--- Print a hexadecimal ---*/
int		ft_print_hex(unsigned int number, int specifier);
char	*ft_htoa(unsigned int number, int specifier);
int		ft_hex_length(unsigned int number);

/*--- Print a pointer adress ---*/
int		ft_print_pointer(unsigned long int number);
char	*ft_ptoa(unsigned long int number);
int		ft_pointer_length(unsigned long int number);

#endif