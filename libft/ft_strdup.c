/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 09:27:35 by cwesseli      #+#    #+#                 */
/*   Updated: 2022/10/18 13:33:10 by cwesseli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ptr;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(s);
	ptr = malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	while (s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

// DESCRIPTION
//        The strdup() function returns a pointer to a new string which is
//        a duplicate of the string s.  Memory for the new string is
//        obtained with malloc(3), and can be freed with free(3).
// RETURN VALUE
//        On success, the strdup() function returns a pointer to the
//        duplicated string.  It returns NULL if insufficient memory was
//        available, with errno set to indicate the error.