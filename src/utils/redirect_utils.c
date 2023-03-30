/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/30 15:56:14 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/03/30 17:30:41 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include <unistd.h>

int	redirect_input(t_node **token, t_smpl_cmd *cmd)
{
	while ((*token)->type == _SPACE || (*token)->type == _TAB ||\
		(*token)->type == COMMENT)
		remove_node(token, cmd);
	if (access((*token)->content, R_OK) == -1)
	{
		printf("Error input: access error\n"); //change to correct error function passing errno
		return (-1);
	}
	cmd->infile = (*token)->content;
	return (0);
}