/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 09:11:16 by ccaljouw      #+#    #+#                 */
/*   Updated: 2022/10/14 10:10:52 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	ucc;
	unsigned char	*ucb;

	ucc = (unsigned char) c;
	ucb = (unsigned char *) b;
	while (len > 0)
	{
		ucb[len - 1] = ucc;
		len--;
	}
	return (b);
}

// NAME
//      memset -- fill a byte string with a byte value

// LIBRARY
//      Standard C Library (libc, -lc)

// SYNOPSIS
//      #include <string.h>
//      void *memset(void *b, int c, size_t len);

// DESCRIPTION
//      The memset() function writes len bytes of value c 
// 		(converted to an unsigned char) to the string b.

// RETURN VALUES
//      The memset() function returns its first argument.

// SEE ALSO
//      bzero(3), memset_pattern(3), memset_s.3, swab(3), wmemset(3)