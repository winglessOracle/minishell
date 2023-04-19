/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isalpha.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/08 15:31:10 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/04/17 16:37:23 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

// NAME isalpha -- alphabetic character test
// SYNOPSIS
//      #include <ctype.h>
//      int isalpha(int c);

// DESCRIPTION
//      The isalpha() function tests for any character for which isupper(3) or 
//      islower(3) is true. The value of the argument must be representable as 
//      an unsigned char or the value of EOF. In the ASCII character set, 
//      this includes the following characters (preceded by their numeric 
//      values, in octal):

// RETURN VALUES
//      The isalpha() function returns zero if the character tests false, 
//      returns 1 if the character tests true and tests true for isupper(3), 
//      returns 2 if the character tests true and tests true for islower(3).