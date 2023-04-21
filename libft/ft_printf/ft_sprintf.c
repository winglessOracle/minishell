/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sprintf.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/16 19:48:09 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/02/18 21:55:04 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*get_argstr(const char *str, char *arg_str, int i, t_print *tp)
{
	i++;
	if (str[i] == '0')
		tp->zero = 1;
	if (ft_strchr(" +#", str[i]) && str[i + 1] == '0')
		tp->zero = 1;
	if (str[i] == '\0')
		return (arg_str);
	i = ft_format(tp, str, i);
	arg_str = ft_strjoin_free_s1(arg_str, ft_write_args(tp));
	arg_str = ft_strjoin_free_s1(arg_str, "\0");
	return (arg_str);
}

char	*ft_itterate_returnstr(const char *str, int i, t_print *tp)
{
	char	*arg_str;
	char	c[2];

	arg_str = ft_calloc(1, sizeof(char));
	if (!arg_str)
		exit(1);
	while (str[i])
	{
		if (str[i] == '%')
		{
			arg_str = get_argstr(str, arg_str, i, tp);
			i++;
		}
		else
		{
			ft_strlcpy(c, str + i, 2);
			arg_str = ft_strjoin_free_s1(arg_str, c);
		}
		if (arg_str == NULL)
			return (NULL);
		i++;
		ft_flags_tp(tp, 1);
	}
	return (arg_str);
}

char	*ft_sprintf(const char *str, ...)
{
	t_print			*tp;
	char			*result;
	int				i;

	tp = (t_print *)malloc(sizeof(t_print));
	if (tp == NULL)
		return (NULL);
	ft_flags_tp(tp, 0);
	va_start(tp->args, str);
	i = 0;
	result = ft_itterate_returnstr(str, i, tp);
	i = tp->tl;
	va_end(tp->args);
	free(tp);
	return (result);
}
