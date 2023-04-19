/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 15:23:55 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/04/19 20:48:05 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	len1;
	size_t	len2;
	char	*ptr;

	i = 0;
	if (!s2)
		return (ft_strdup(s1));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	ptr = malloc((len1 + len2 + 1) * sizeof(char));
	if (ptr == 0)
		return (NULL);
	while (i < len1)
	{
		ptr[i] = s1[i];
		i++;
	}
	while (i < (len1 + len2))
	{
		ptr[i] = s2[i - len1];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

// Parameters 
// 		s1: The prefix string.
// 		s2: The suffix string.
// Return value 
// 		The new string.
// 		NULL if the allocation fails.
// External functs. malloc
// Description Allocates (with malloc(3)) and returns a new string, which is 
// the result of the concatenation of ’s1’ and ’s2’.