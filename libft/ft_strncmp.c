/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 09:27:54 by cwesseli      #+#    #+#                 */
/*   Updated: 2022/10/18 13:37:18 by cwesseli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

// DESCRIPTION
//        The strncmp() function shall compare not more than n bytes (bytes
//        that follow a NUL character are not compared) from the array
//        pointed to by s1 to the array pointed to by s2.
//        The sign of a non-zero return value is determined by the sign of
//        the difference between the values of the first pair of bytes
//        (both interpreted as type unsigned char) that differ in the
//        strings being compared.
// RETURN VALUE
//        Upon successful completion, strncmp() shall return an integer
//        greater than, equal to, or less than 0, if the possibly null-
//        terminated array pointed to by s1 is greater than, equal to, or
//        less than the possibly null-terminated array pointed to by s2
//        respectively.