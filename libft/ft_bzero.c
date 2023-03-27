/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 09:19:37 by ccaljouw      #+#    #+#                 */
/*   Updated: 2022/10/17 13:45:07 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}

// NAME
//      bzero -- write zeroes to a byte string

// LIBRARY
//      Standard C Library (libc, -lc)

// SYNOPSIS
//      #include <strings.h>
//      void	bzero(void *s, size_t n);

// DESCRIPTION
//      The bzero() function writes n zeroed bytes to the string s.  
// 		If n is zero, bzero() does nothing.