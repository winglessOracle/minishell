/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.42      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/21 16:56:25 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/02/18 19:05:46 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <limits.h>
# include "../libft.h"

// struct to store flags
typedef struct s_print
{
	va_list	args;
	int		s;
	char	type;
	int		pound;
	int		zero;
	int		plus;
	int		min;
	int		sp;
	int		width;
	int		dot;
	int		strlim;
	int		tl;
	int		vl;
	char	s_1;
	int		neg;
	int		start;
	int		with_sign;
}	t_print;
int		ft_printf(const char *str, ...);
int		ft_fprintf(int fd, const char *str, ...);
char	*ft_sprintf(const char *str, ...);

//mandatory
void	ft_setwidth(t_print *tp, char s);
int		ft_setflags(t_print *tp, char s);
int		ft_format(t_print *tp, const char *str, int i);
char	*ft_write_args(t_print *tp);
char	*ft_itoa_base_u(unsigned long n, char *base, t_print *tp);
char	*ft_itoa_base(long long n, char *base, t_print *tp);

// bonus
t_print	*ft_flags_tp(t_print	*tp, int reset);
char	*ft_processflags(char *str, t_print *tp);
char	*ft_starti(char *str, t_print *tp);
char	*ft_sign(char *str, t_print *tp);

#endif