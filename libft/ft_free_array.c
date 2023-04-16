/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_array.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/30 12:34:20 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/04/16 11:56:23 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		ft_free(arr[i]);
		i++;
	}
	free(arr);
	arr = 0;
}
