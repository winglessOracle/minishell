/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 09:27:44 by cwesseli      #+#    #+#                 */
/*   Updated: 2022/10/18 13:20:36 by cwesseli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t		len_src;
	size_t		i;

	len_src = ft_strlen(src);
	i = 0;
	if (dstsize == 0)
		return (len_src);
	while (i < (dstsize - 1) && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (len_src);
}

// DESCRIPTION
// The strlcpy() and strlcat() functions copy 
// and concatenate strings with the same input parameters
// They are designed to be safer, more consistent, and less 
// error prone replacements for the easily misused functions 
// strncpy(3) and strncat(3). strlcpy() and strlcat() take 
// the full size of the destination buffer and 
// guarantee NUL-termination if there is room.  Note that 
// room for the NUL should be included indstsize.
// strlcpy() copies up to dstsize - 1 characters from the 
// string src to dst, NUL-terminating the result if dstsize 
// is not 0. If the src and dst strings overlap, the behavior is undefined.

// RETURN VALUES
// ength of the string they tried to create.  
// For strlcpy() that means the length of src.
// If the return value is >= dstsize, 
// the output string has been truncated.  
// It is the caller's responsibility to handle this.