/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.42      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/21 16:56:21 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/02/17 09:26:05 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_itterate(const char *str, int i, t_print *tp, int fd)
{
	char	*arg_str;

	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			if (str[i] == '0')
				tp->zero = 1;
			if (ft_strchr(" +#", str[i]) && str[i + 1] == '0')
				tp->zero = 1;
			if (str[i] == '\0')
				break ;
			i = ft_format(tp, str, i);
			arg_str = ft_write_args(tp);
			tp->tl += write(fd, arg_str, tp->width);
			free(arg_str);
		}
		else
			tp->tl += write(fd, &str[i], 1);
		if (tp->tl == -1)
			break ;
		i++;
		ft_flags_tp(tp, 1);
	}
}

int	ft_printf(const char *str, ...)
{
	t_print			*tp;
	int				i;

	tp = (t_print *)malloc(sizeof(t_print));
	if (tp == NULL)
		return (-1);
	ft_flags_tp(tp, 0);
	va_start(tp->args, str);
	i = 0;
	ft_itterate(str, i, tp, 1);
	i = tp->tl;
	va_end(tp->args);
	free(tp);
	return (i);
}

int	ft_fprintf(int fd, const char *str, ...)
{
	t_print			*tp;
	int				i;

	tp = (t_print *)malloc(sizeof(t_print));
	if (tp == NULL)
		return (-1);
	ft_flags_tp(tp, 0);
	va_start(tp->args, str);
	i = 0;
	ft_itterate(str, i, tp, fd);
	i = tp->tl;
	va_end(tp->args);
	free(tp);
	return (i);
}

// You have to recode the printf() function from libc.
// 
// The prototype of ft_printf() is:
// int ft_printf(const char *, ...);
// 
// Here are the requirements:
// 	• Don’t implement the buffer management of the original printf().
// 	• Your function has to handle the following conversions: cspdiuxX%
// 	• Your function will be compared against the original printf().
// 	• You must use the command ar to create your library.
// Using the libtool command is forbidden.
// 	• Your libftprintf.a has to be created at the root of your repository.
// 
// You have to implement the following conversions:
// 	• %c Prints a single character.
// 	• %s Prints a string (as defined by the common C convention).
// 	• %p The void * pointer argument has to be printed in hexadecimal format.
// 	• %d Prints a decimal (base 10) number.
// 	• %i Prints an integer in base 10.
// 	• %u Prints an unsigned decimal (base 10) number.
// 	• %x Prints a number in hexadecimal (base 16) lowercase format.
// 	• %% Prints a percent sign.
// 	• %X Prints a number in hexadecimal (base 16) uppercase format.