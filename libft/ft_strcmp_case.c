/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strcmp_case.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 09:27:54 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/04/20 16:05:19 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp_case(const char *s1, const char *s2, int (setcase)(int))
{
	size_t	i;

	if (!s1 || !s2)
		return (-1);
	i = 0;
	while ((s1[i] || s2[i]))
	{
		if (setcase(s1[i]) != setcase(s2[i]))
			return (setcase(s1[i]) - setcase(s2[i]));
		i++;
	}
	return (0);
}
