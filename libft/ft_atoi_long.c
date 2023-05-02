/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi_long.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 09:26:11 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/05/01 10:46:02 by cwesseli      ########   odam.nl         */
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
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0) //added this line
			return (-1);
		output = output * 10 + (str[i] - '0');
		i++;
	}
	return (sign * output);
}
