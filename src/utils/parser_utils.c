/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/29 20:18:41 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/04 10:19:58 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int		todo(t_node **token, t_smpl_cmd *cmd)
{
	printf("not handeled yet: type: %d, content: %s\n", (*token)->type, (*token)->content);
	(*token) = (*token)->next;
	remove_node(token, cmd);
	return (0);
}

int remove_node(t_node **token, t_smpl_cmd *cmd)
{	
	(void)cmd;
	t_node	*temp;
	
	if (!*token)
		return (-1);
	temp = lstpop(token);
	lstdelone(temp, delete_content);
	return (0);
}

int	set_type_word(t_node **token, t_smpl_cmd *cmd)
{
	if (cmd->cmd_argc == 0)
		(*token)->type = NAME;
	else
		(*token)->type = WORD;
	return (0);
}

int	set_cmd_end(t_node **token, t_smpl_cmd *cmd)
{
	int check;

	check = check_pipe(*token, cmd);
	remove_node(token, cmd);
	return (check);
}

