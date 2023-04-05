/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/30 15:56:14 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/05 13:49:08 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include <unistd.h>


int	redirect(t_node **tokens, t_smpl_cmd *cmd)
{
	printf("*REDIRECT* %s\n", (*tokens)->content);
	remove_node(tokens, cmd);
	return (0);
}