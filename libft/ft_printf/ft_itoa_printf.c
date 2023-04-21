/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa_printf.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.42      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/15 21:18:59 by ccaljouw      #+#    #+#                 */
/*   Updated: 2022/11/09 11:39:07 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int	ft_size(long long n, int baselen, t_print *tp)
{
	int		len;

	len = 0;
	if (n < 0)
	{
		tp->neg = 1;
		tp->with_sign = 1;
	}
	if (n == 0 || !n)
	{
		if ((tp->strlim > 0 || tp->dot == 0) \
			|| (tp->strlim == -1 && tp->width == 0 && tp->with_sign == 0))
			len++;
		tp->s_1 = 1;
		n = 0;
	}
	while (n != 0)
	{
		n /= baselen;
		len++;
	}
	return (len);
}

static	int	ft_size_u(unsigned long n, int baselen, t_print *tp)
{
	int		len;

	len = 0;
	if (n == 0 || !n)
	{
		if ((tp->strlim > 0 || tp->dot == 0) \
			|| (tp->strlim == -1 && tp->width == 0 && tp->with_sign == 0))
			len++;
		tp->s_1 = 1;
		if (tp->s == 'x' || tp->s == 'X')
			tp->with_sign = 0;
		n = 0;
	}
	while (n != 0)
	{
		n /= baselen;
		len++;
	}
	return (len);
}

char	*ft_sign(char *str, t_print *tp)
{
	if (tp->with_sign == 1)
	{
		if (tp->sp == 1)
			str[tp->start] = ' ';
		if (tp->plus == 1)
			str[tp->start] = '+';
		if (tp->neg == 1)
			str[tp->start] = '-';
	}
	if (tp->with_sign == 2)
	{
		if (tp->s == 'X')
			ft_memcpy(str + tp->start, "0X", 2);
		else
			ft_memcpy(str + tp->start, "0x", 2);
	}
	if (tp->dot == 1 && tp->min == 1)
		tp->start = tp->strlim - tp->vl;
	else if (tp->min == 1 || tp->zero == 1)
		tp->start = tp->with_sign;
	else
		tp->start = tp->width - tp->vl;
	return (str);
}

char	*ft_itoa_base_u(unsigned long n, char *base, t_print *tp)
{
	char	*str;
	int		baselen;

	str = 0;
	if (tp->s == 'x' || tp->s == 'X' || tp->s == 'u')
		n = (unsigned int) n;
	baselen = ft_strlen(base);
	tp->vl = ft_size_u(n, baselen, tp);
	str = ft_starti(str, tp);
	if (str == NULL)
		return (str);
	if (tp->dot == 1 && tp->min == 1)
		tp->start = tp->strlim - 1;
	else if (tp->min == 1)
		tp->start = tp->vl + tp->with_sign - 1;
	else
		tp->start = tp->width - 1;
	if (n == 0 && tp->strlim != 0)
		str[tp->start] = base[n % baselen];
	while (n > 0)
	{
		str[tp->start--] = base[n % baselen];
		n /= baselen;
	}
	return (str);
}

char	*ft_itoa_base(long long n, char *base, t_print *tp)
{
	char	*str;
	int		baselen;

	str = 0;
	baselen = ft_strlen(base);
	tp->vl = ft_size(n, baselen, tp);
	if (n < 0)
		n = -n;
	str = ft_starti(str, tp);
	if (str == NULL)
		return (str);
	if (tp->dot == 1 && tp->min == 1)
		tp->start = tp->strlim - 1;
	else if (tp->min == 1)
		tp->start = tp->vl + tp->with_sign - 1;
	else
		tp->start = tp->width - 1;
	if (n == 0 && tp->strlim != 0 && !(tp->strlim <= tp->with_sign))
		str[tp->start] = base[n % baselen];
	while (n > 0)
	{
		str[tp->start--] = base[n % baselen];
		n /= baselen;
	}
	return (str);
}

// Parameters       n: the integer to convert.
// 
// Return value     The string representing the integer.
//                  NULL if the allocation fails.
// 
// External functs. malloc
// 
// Description 
// Allocates (with malloc(3)) and returns a string
// representing the integer received as an argument.
// Negative numbers must be handled.
