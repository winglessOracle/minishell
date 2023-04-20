/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 13:17:55 by ccaljouw      #+#    #+#                 */
/*   Updated: 2022/10/14 10:10:05 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*csrc;
	unsigned char	*cdst;

	if (!src && !dst)
		return (NULL);
	csrc = (unsigned char *) src;
	cdst = (unsigned char *) dst;
	i = 0;
	while (i < n)
	{
		cdst[i] = csrc[i];
		i++;
	}
	return (dst);
}

// NAME
//      memcpy -- copy memory area

// LIBRARY
//      Standard C Library (libc, -lc)

// SYNOPSIS
//      #include <string.h>
//      void *	memcpy(void *restrict dst, const void *restrict src, size_t n);

// DESCRIPTION
//      The memcpy() function copies n bytes from memory area src to memory 
// 		area dst. If dst and src overlap, behavior is undefined.  Applica-
//      tions in which dst and src might overlap should use memmove(3) instead.

// RETURN VALUES
//      The memcpy() function returns the original value of dst.