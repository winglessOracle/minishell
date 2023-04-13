/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/18 13:15:50 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/02/15 07:20:05 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_wordcount(char const *s, char c)
{
	size_t	count;
	int		i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static size_t	ft_wordlen(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	i;
	size_t	j;
	size_t	words;
	size_t	len;

	i = 0;
	j = 0;
	words = ft_wordcount(s, c);
	arr = malloc((words + 1) * sizeof(char *));
	if (arr == NULL)
		return (NULL);
	while (j < words)
	{
		while (s[i] && s[i] == c)
			i++;
		len = ft_wordlen(s + i, c);
		arr[j] = ft_substr(s, i, len);
		if (arr[j] == NULL)
			return (ft_freearr(arr, j - 1));
		i = i + len;
		j++;
	}
	arr[j] = NULL;
	return (arr);
}

// Parameters 
//      s: The string to be split.
//      c: The delimiter character.
// Return value 
//      The array of new strings resulting from the split.
//      NULL if the allocation fails.
// External functs. malloc, free
// Description Allocates (with malloc(3)) and returns an array of strings 
// obtained by splitting ’s’ using the
// character ’c’ as a delimiter. The array must end with a NULL pointer.