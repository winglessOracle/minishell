/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 14:22:25 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/03/29 16:10:21 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"


// t_node	*less(t_node **token)
// t_node	*great(t_node **token);
// t_node	*dless(t_node **token);
// t_node	*dgreat(t_node **token);
// t_node	*pipe(t_node **token);
// t_node	*new_line(t_node **token);
// t_node	*expand(t_node **token);
// t_node	*assign(t_node **token);

void	todo(t_node **token)
{
	printf("not handeled yet: type: %d, content: %s\n", (*token)->type, (*token)->content);
	(*token) = (*token)->next;
}

t_smpl_cmd	*parse_simple_command(t_node *token, t_smpl_cmd *cmd)
{	
	if (!token)
		return (cmd);
	if (token)
	{
		if (token->type == WORD || token->type == SQUOTE || token->type == DQUOTE)
			lstadd_back(&cmd->cmd_var, lstpop(&token));
		else
			parse[token->type](&token);
	}
	cmd = parse_simple_command(token, cmd);
	return (cmd);
}


// if COMMENT || SPACE || TAB -> remove?
// if LESS -> check next and set input 
// if GREAT -> check next and set output TRUNC
// if DLESS -> io_here (set value next node in master_struct?)
// if DGREAT -> check next set output append
// if PIPE -> end simple command
// if NEW_LINE -> end simple command and pipeline
// if EXPAND -> expand to (env)value
	// if $? -> expand to last exit status
// if ASSIGN -> assign variable
