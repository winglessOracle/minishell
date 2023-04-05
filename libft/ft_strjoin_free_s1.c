/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin_free_s1.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/05 14:27:38 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/05 14:27:52 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free_s1(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*ptr;

	if (!s1)
	{
		s1 = malloc((ft_strlen(s2) + 1) * sizeof(char));
		if (!s1)
			return (NULL);
		ft_strlcpy(s1, s2, (ft_strlen(s2) + 1));
		return (s1);
	}
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	ptr = malloc((len1 + len2 + 1) * sizeof(char));
	if (ptr == 0)
	{
		free(s1);
		return (NULL);
	}
	ft_strlcpy(ptr, s1, len1 + 1);
	ft_strlcpy(ptr + len1, s2, len2 + 1);
	ptr[len1 + len2] = '\0';
	free(s1);
	return (ptr);
}