/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/30 15:56:14 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/05 12:54:33 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include <unistd.h>

// else if (token->content[0] == '<' && token->content[0] == '<')
// 	return (DLESS);
// else if (token->content[0] == '>' && token->content[0] == '>')
// 	return (DGREAT);

// int	redirect_input(t_node **token, t_smpl_cmd *cmd)
// {	
// 	remove_node(token, cmd);
// 	while ((*token)->type == BLANK|| \
// 		(*token)->type == COMMENT)
// 		remove_node(token, cmd);
// 	// if ((*token)->type == ASSIGN || (*token)->type == EXPAND)
// 	// 	state = parse[tokens->type](&tokens, *cmd);
// 	if (access((*token)->content, R_OK) == -1)
// 	{
// 		printf("Error input: access error\n"); //change to correct error function passing errno
// 		return (-1);
// 	}
// 	cmd->infile = (*token)->content;
// 	remove_node(token, cmd);
// 	return (0);
// }

// int	redirect_output(t_node **token, t_smpl_cmd *cmd)
// {
// 	// also check or create file here?
// 	remove_node(token, cmd);
// 	while ((*token)->type == BLANK|| \
// 		(*token)->type == COMMENT)
// 		remove_node(token, cmd);
// 	// if ((*token)->type == ASSIGN || (*token)->type == EXPAND)
// 	// 	state = parse[tokens->type](&tokens, *cmd);
// 	cmd->outfile = (*token)->content;
// 	remove_node(token, cmd);
// 	return (0);
// }

// int	set_here_end(t_node **token, t_smpl_cmd *cmd)
// {
// 	remove_node(token, cmd);
// 	while ((*token)->type == BLANK || \
// 		(*token)->type == COMMENT)
// 		remove_node(token, cmd);
// 	// if ((*token)->type == ASSIGN || (*token)->type == EXPAND)
// 	// 	state = parse[tokens->type](&tokens, *cmd);
// 	cmd->here_end = (*token)->content;
// 	remove_node(token, cmd);
// 	return (0);
// }

// int	set_append(t_node **token, t_smpl_cmd *cmd)
// {
// 	int	check;
	
// 	check = redirect_output(token, cmd);
// 	cmd->append = 1;
// 	return (check);
// }