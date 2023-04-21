/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_getargs.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.42      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 07:14:04 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/02/17 09:27:08 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_starti(char *str, t_print *tp)
{
	str = ft_processflags(str, tp);
	if (str == NULL)
		return (str);
	if (tp->min == 1 || tp->zero == 1)
		tp->start = 0;
	else if (tp->dot == 1)
		tp->start = tp->width - tp->strlim;
	else
		tp->start = tp->width - tp->vl - tp->with_sign;
	ft_memset(str, ' ', tp->width);
	if (tp->min == 1 && tp->dot == 1)
	{
		ft_memset(str, '0', tp->strlim);
		ft_memset(str + tp->strlim, ' ', tp->width - tp->strlim);
	}
	else if (tp->min == 1)
		ft_memset(str, ' ', tp->width);
	else if (tp->type == 'd' || tp->type == 'x')
	{
		ft_memset(str, '0', tp->width);
		ft_memset(str, ' ', tp->start);
	}
	ft_sign(str, tp);
	return (str);
}

static char	*ft_printfstr(char *str, t_print *tp)
{
	char	*temp;

	if (str && *str == 0 && tp->width == -1)
	{
		tp->width = 0;
		tp->s_1 = 1;
	}
	else if (!str)
	{
		str = "(null)";
		tp->vl = 6;
		tp->s_1 = 1;
	}
	else
		tp->vl = ft_strlen(str);
	tp->with_sign = 0;
	if (tp->dot == 1 && tp->strlim < tp->vl)
		tp->vl = tp->strlim;
	if (tp->strlim > tp->vl && tp->dot == 1)
		tp->strlim = tp->vl;
	temp = ft_starti(str, tp);
	if (temp == NULL)
		return (temp);
	ft_memcpy(temp + tp->start, str, tp->vl);
	return (temp);
}

static char	*ft_printfchr(char *temp, t_print *tp)
{
	char	c;

	if (tp->s == 'c')
		c = (char)va_arg(tp->args, int);
	if (tp->s == '%')
		c = '%';
	tp->vl = 1;
	temp = ft_starti(temp, tp);
	if (temp == NULL)
		return (temp);
	temp[tp->start] = c;
	return (temp);
}

char	*ft_getargs(char *str, t_print *tp)
{
	if (tp->s == 'p' || tp->s == 'x')
		str = ft_itoa_base_u(va_arg(tp->args, unsigned long), \
		"0123456789abcdef", tp);
	else if (tp->s == 'X')
		str = ft_itoa_base_u(va_arg(tp->args, unsigned int), \
		"0123456789ABCDEF", tp);
	else if (tp->s == 'd' || tp->s == 'i')
		str = ft_itoa_base(va_arg(tp->args, int), "0123456789", tp);
	else if (tp->s == 'u')
		str = ft_itoa_base_u(va_arg(tp->args, unsigned int), \
		"0123456789", tp);
	else if (tp->s == 's')
		str = ft_printfstr(va_arg(tp->args, char *), tp);
	else if (tp->s == 'c' || tp->s == '%')
		str = ft_printfchr(str, tp);
	else
		tp->tl = -1;
	return (str);
}

char	*ft_write_args(t_print *tp)
{
	char		*str;

	str = 0;
	str = ft_getargs(str, tp);
	if (str == NULL)
		tp->tl = -1;
	if (tp->tl == -1)
	{
		free(str);
		return (NULL);
	}
	return (str);
}
