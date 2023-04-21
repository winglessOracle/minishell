/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin_free_s2.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/05 14:27:38 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/20 14:06:22 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free_s2(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*ptr;

	if (!s1)
		return (s2);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	ptr = malloc((len1 + len2 + 1) * sizeof(char));
	if (ptr == 0)
	{
		free(s2);
		return (NULL);
	}
	ft_strlcpy(ptr, s1, len1 + 1);
	ft_strlcpy(ptr + len1, s2, len2 + 1);
	ptr[len1 + len2] = '\0';
	free(s2);
	return (ptr);
}
