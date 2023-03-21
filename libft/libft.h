/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: carlo <carlo@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 09:28:59 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/03/21 09:58:25 by cwesseli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <stdarg.h>
# include <limits.h>
// # define MAX_OPEN 10240

// # ifndef BUFFER_SIZE
// #  define BUFFER_SIZE 16
// # endif

// typedef struct s_print
// {
// 	va_list				args;
// 	unsigned long int	len;
// 	char				*valid_char;
// 	char				*length;
// 	char				*base_h;
// 	char				*base_h_up;
// 	char				*base_d;
// }	t_print;

// typedef struct s_list
// {
// 	void			*content;
// 	struct s_list	*next;
// }	t_list;

// char	*ft_strnstr(const char *big, const char *little, size_t len);
// size_t	ft_strlcpy(char *dst, const char *src, size_t size);
// size_t	ft_strlcat(char *dst, const char *src, size_t size);
// char	*ft_strjoin(char const *s1, char const *s2);
// char	**ft_split(char const *s, char c);
// char	*ft_substr(char const *s, unsigned int start, size_t len);
// int		ft_isalpha(int c);
// size_t	ft_strlen(const char *s);
// int		ft_isdigit(int c);
// int		ft_isalnum(int c);
// int		ft_isascii(int c);
// int		ft_isprint(int c);
// int		ft_toupper(int c);
// int		ft_tolower(int c);
// int		ft_atoi(const char *str);
// void	ft_bzero(void *s, size_t n);
// int		ft_strncmp(const char *s1, const char *s2, size_t n);
// int		ft_strrcmp(const char *s1, const char *s2, size_t n);
// char	*ft_strrchr(const char *s, int c);
// void	*ft_memchr(const void *s, int c, size_t n);
// char	*ft_strchr(const char *s, int c);
// int		ft_memcmp(const void *s1, const void *s2, size_t n);
// void	*ft_memcpy(void *dest, const void *src, size_t n);
// void	*ft_memset(void *s, int c, size_t n);
// void	*ft_memmove(void *dest, const void *src, size_t n);
// char	*ft_strdup(const char *s);
// void	*ft_calloc(size_t nelem, size_t elsize);
// char	*ft_strtrim(char const *s1, char const *set);
// char	*ft_itoa(int n);
// char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
// void	ft_striteri(char *s, void (*f)(unsigned int, char*));
// void	ft_putchar_fd(char c, int fd);
// void	ft_putstr_fd(char *s, int fd);
// void	ft_putendl_fd(char *s, int fd);
// void	ft_putnbr_fd(int n, int fd);
// t_list	*ft_lstnew(void *content);
// void	ft_lstadd_front(t_list **lst, t_list *new);
// int		ft_lstsize(t_list *lst);
// t_list	*ft_lstlast(t_list *lst);
// void	ft_lstadd_back(t_list **lst, t_list *new);
// void	ft_lstdelone(t_list *lst, void (*del)(void *));
// void	ft_lstclear(t_list **lst, void (*del)(void *));
// void	ft_lstiter(t_list *lst, void (*f)(void *));
// t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
// int		ft_isspace(int c);
// void	ft_putchar(unsigned const char c);
// void	ft_putstr(const char *str);

// // for ft_printf
// int		ft_printf(const char *str, ...);
// void	ft_print_char(t_print *list);
// void	ft_print_str(t_print *list);
// void	ft_print_dec(t_print *list, char c);
// void	ft_print_str_dec(t_print *list, char *str);
// void	ft_print_hex(t_print *list, char c);
// void	ft_printf_itoa(t_print *list, long int n, char *base);
// void	ft_printf_itoa_u(t_print *list, unsigned long long int n, char *base);
// int		check_ident(t_print *list, char c);
// void	check_letter(t_print *list, char c);
// int		check_input(t_print *list, char *str);

// // for ft_get_next_line
// char	*get_next_line(int fd);
// char	*read_and_join(int fd, char *str);
// char	*ft_strjoin_gnl(char *str, char *buffer);
// int		ft_strlen_gnl(char *str);
// char	*get_new_line(char *str);
// char	*get_new_string(char *passed_line);
// int		ft_findchr(char *s, char c);
// void	free_str(char *str);

// //own
// int		ft_check_extention(const char *file, const char *extention);
void	ft_free(void *param);
void	ft_free_array(char **arr);
//void	ft_free_array_int(int **arr);
// void	ft_check_params(int argc, char *argv, int n);
// char	*ft_strjoin_free(char *s1, char const *s2);
// int		ft_wordcount(const char *s, char c);
// long	ft_atoi_long(const char *str);

// # define COLOR_RED "\x1b[0;31m"
// # define COLOR_GREEN "\x1b[0;32m"
// # define COLOR_YELLOW "\x1b[0;33m"
// # define COLOR_BLUE "\x1b[0;34m"
// # define COLOR_MAGENTA "\x1b[0;35m"
// # define COLOR_CYAN "\x1b[0;36m"
// # define COLOR_WHITE "\x1b[0;37m"
// # define COLOR_BLACK "\x1b[0;30m"
// # define COLOR_NORMAL "\x1b[m"

#endif
