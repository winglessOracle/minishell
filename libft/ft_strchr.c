/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 09:27:28 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/03/22 09:27:25 by carlo         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*checker;
	char	to_check;

	if (s == NULL)
		return (NULL);
	checker = (char *)s;
	to_check = (char)c;
	while (*checker != to_check && *checker != '\0')
		checker++;
	if (*checker != to_check)
		return (NULL);
	return (checker);
}
