/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi_long.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 09:26:11 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/04/29 22:24:14 by carlo         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

long	ft_atoi_long(const char *str)
{
	int			i;
	long int	output;
	long int	sign;

	i = 0;
	output = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (ft_isdigit(str[i]) == 0)
		return (-5);
	while (ft_isdigit(str[i]))
	{
		output = output * 10 + (str[i] - '0');
		i++;
	}
	return (sign * output);
}
