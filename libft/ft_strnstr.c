/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 09:27:59 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/03/27 17:41:05 by cwesseli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	len_n;

	len_n = ft_strlen(needle);
	if (len_n == 0)
		return ((char *)haystack);
	while (*haystack && len-- >= len_n)
	{
		if (!(ft_strncmp((char *)haystack, (char *)needle, len_n)))
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}
