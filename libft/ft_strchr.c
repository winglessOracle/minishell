/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 09:27:28 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/03/26 20:33:13 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char *s, int c)
{
	char	*checker;
	char	to_check;

	if (s == NULL)
		return (NULL);
	checker = s;
	to_check = (char)c;
	while (*checker != to_check && *checker != '\0')
		checker++;
	if (*checker != to_check)
		return (NULL);
	return (checker);
}
