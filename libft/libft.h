/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: carlo <carlo@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 09:28:59 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/04/17 16:37:36 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <stdarg.h>
# include <limits.h>

char	*ft_strchr(char *s1, int c);
char	*ft_strdup(const char *s);
int		ft_isspace(int c);
void	ft_free(void *param);
void	ft_free_array(char **arr);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin_free_s1(char *s1, char *s2);
char	**ft_split(char const *s, char c);
char	**ft_freearr(char **arr, int j);
int		ft_isalpha(int c);


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
