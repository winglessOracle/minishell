/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_freearr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/15 07:20:23 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/02/16 10:17:23 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_freearr(char **arr, int j)
{
	if (j == 0)
	{
		while (arr[j])
		{
			free(arr[j]);
			j++;
		}
	}
	else
	{
		while (j >= 0)
		{
			free(arr[j]);
			j--;
		}
	}
	free(arr);
	return (0);
}
