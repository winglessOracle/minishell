/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/15 21:18:59 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/04/20 12:03:51 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_size(int n)
{
	int		len;

	len = 0;
	if (n < 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*ft_nzero(void)
{
	char	*str;

	str = ft_calloc(2, sizeof(char));
	if (str == 0)
		return (NULL);
	str[0] = '0';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	long	numb;

	numb = (long) n;
	i = ft_size(numb);
	if (numb == 0)
		return (ft_nzero());
	str = malloc((i + 1) * sizeof(char));
	if (str == 0)
		return (NULL);
	str[i--] = '\0';
	if (numb < 0)
	{
		str[0] = '-';
		numb = -numb;
	}
	while (numb > 0)
	{
		str[i--] = numb % 10 + '0';
		numb /= 10;
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