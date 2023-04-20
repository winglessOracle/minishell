/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_set.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/06 19:31:32 by cariencaljo   #+#    #+#                 */
/*   Updated: 2022/11/09 11:29:32 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_print	*ft_flags_tp(t_print	*tp, int reset)
{
	tp->s = 0;
	tp->type = 0;
	tp->pound = 0;
	tp->zero = 0;
	tp->plus = 0;
	tp->min = 0;
	tp->sp = 0;
	tp->width = -1;
	tp->dot = 0;
	tp->strlim = 0;
	tp->vl = 0;
	tp->s_1 = 0;
	tp->neg = 0;
	tp->start = 0;
	tp->with_sign = 0;
	if (reset == 0)
		tp->tl = 0;
	return (tp);
}

char	*ft_processflags(char *str, t_print *tp)
{
	if (tp->zero == 1 && tp->dot == 1)
		tp->zero = 0;
	if (tp->width <= tp->strlim)
	{
		tp->strlim += tp->with_sign;
		tp->width = tp->strlim;
	}
	if (tp->width > tp->strlim && tp->dot == 1)
			tp->strlim += tp->with_sign;
	if (tp->width < tp->vl + tp->with_sign)
		tp->width = tp->vl + tp->with_sign;
	if (tp->vl > tp->strlim && tp->strlim > tp->width)
		tp->strlim = tp->width;
	if (tp->strlim < tp->vl + tp->with_sign)
		tp->strlim = tp->vl + tp->with_sign;
	if (tp->width < tp->strlim && tp->dot == 1)
		tp->width = tp->strlim;
	str = ft_calloc(tp->width + tp->with_sign + 1, sizeof(char));
	if (str == NULL)
	{
		tp->tl = -1;
		return (NULL);
	}
	return (str);
}
