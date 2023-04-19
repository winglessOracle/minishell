/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 15:02:31 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/03/28 09:32:03 by cwesseli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	strlen;

	strlen = ft_strlen(s);
	if (!s || strlen <= start)
		return (ptr = ft_calloc(1, sizeof(char)));
	if (len > strlen - start)
		len = strlen - start;
	ptr = ft_calloc((len + 1), sizeof(char));
	if (ptr == 0)
		return (NULL);
	ft_strlcpy(ptr, s + start, len + 1);
	return (ptr);
}

// Parameters 
// 		s: The string from which to create the substring.
// 		start: The start index of the substring in the string ’s’.
// 		len: The maximum length of the substring.
// Return value		
// 		The substring.
// 		NULL if the allocation fails.
// External functs. malloc
//
// Description Allocates (with malloc(3)) and returns a substring from the 
// string ’s’. The substring begins at index ’start’ and is of maximum size 
// ’len’.