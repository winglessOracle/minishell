/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_format.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/16 18:08:11 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/02/16 18:09:22 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_setwidth(t_print *tp, char s)
{
	if (tp->dot == 1)
	{
		if (tp->strlim == -1)
			tp->strlim = 0;
		tp->strlim = (tp->strlim * 10) + (s - '0');
	}
	else
	{
		if (tp->width == -1)
			tp->width = 0;
		tp->width = (tp->width * 10) + (s - '0');
	}
}

int	ft_setflags(t_print *tp, char s)
{
	if (s == '-')
		tp->min = 1;
	else if (s == '.')
		tp->dot = 1;
	else if (s == '#')
		tp->pound = 1;
	else if (s == ' ')
		tp->sp = 1;
	else if (s == '+')
		tp->plus = 1;
	else if (ft_isdigit(s))
		ft_setwidth(tp, s);
	else
		tp->tl = -1;
	if (tp->sp == 1 || tp->plus == 1)
		tp->with_sign = 1;
	return (1);
}

int	ft_format(t_print *tp, const char *str, int i)
{
	while (!ft_strchr("csdiupxX%", str[i]))
	{
		tp->s = str[i];
		i += ft_setflags(tp, str[i]);
	}
	if (ft_strchr("px", str[i]))
		tp->type = 'x';
	if (ft_strchr("X", str[i]))
		tp->type = 'x';
	if (ft_strchr("diu", str[i]))
		tp->type = 'd';
	if (ft_strchr("cs", str[i]))
		tp->type = 's';
	if (ft_strchr("%", str[i]))
		tp->type = '%';
	if (tp->tl == -1)
		return (tp->tl);
	tp->s = str[i];
	if (tp->s == 'p' || (tp->type == 'x' && tp->pound == 1))
		tp->with_sign = 2;
	return (i);
}
