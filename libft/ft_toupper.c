/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_toupper.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 13:47:57 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/04/20 15:24:44 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}

// NAME
//      toupper, toupper_l -- lower case to upper case letter conversion

// LIBRARY
//      Standard C Library (libc, -lc)

// SYNOPSIS
//      #include <ctype.h>
//      int	toupper(int c);

//      #include <ctype.h>
//      #include <xlocale.h>

//      int
//      toupper_l(int c, locale_t loc);

// DESCRIPTION
//      The toupper() function converts a lower-case letter to the 
// 		corresponding upper-case letter.  The argument must be 
// 		representable as an unsigned char or the value of EOF.

//      Although the toupper() function uses the current locale, the 
// 		toupper_l() function may be passed a locale directly. 
// 		See xlocale(3) for more information.

// RETURN VALUES
//      If the argument is a lower-case letter, the toupper() function returns
// 		the corresponding upper-case letter if there is one; otherwise,
//      the argument is returned unchanged.

// COMPATIBILITY
//      The 4.4BSD extension of accepting arguments outside of the range of the 
// 		unsigned char type in locales with large character sets is considered 
// 		obsolete and may not be supported in future releases.  The towupper() 
// 		function should be used instead.

// SEE ALSO
//      ctype(3), isupper(3), towupper(3), xlocale(3)