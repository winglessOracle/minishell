/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strcmp_uppercase.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 09:27:54 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/04/20 15:57:20 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp_uc(const char *s1, const char *s2)
{
	size_t	i;

	if (!s1 || !s2)
		return (-1);
	i = 0;
	while ((s1[i] || s2[i]))
	{
		if (ft_toupper(s1[i]) != ft_toupper(s2[i]))
			return ((unsigned char)ft_toupper(s1[i]) \
				- (unsigned char)ft_toupper(s2[i]));
		i++;
	}
	return (0);
}
