/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 15:51:21 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/03/27 17:50:32 by cwesseli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ptr;
	unsigned int	ls;

	ls = ft_strlen((char *) s);
	if (ls - start < len)
		len = ls - start;
	if (!s || ls < start)
	{
		ptr = malloc(sizeof(char) * 1);
		if (!ptr)
			return (NULL);
		ptr[0] = '\0';
		return (ptr);
	}
	ptr = malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s + start, len + 1);
	return (ptr);
}

/*Returns the substring of the given string at 
the given start position with the given length 
(or smaller if the length of the original string
is less than start + length, or length is bigger
than MAXSTRINGLEN).
*/