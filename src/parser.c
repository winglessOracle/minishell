/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 14:22:25 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/03/29 12:24:57 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

t_node	*remove_node(t_node **token)
{	
	t_node	*temp;
	
	temp = lstpop(token);
	lstdelone(temp, delete_content);
	return (NULL);
}

// t_node	*less(t_node **token)
// t_node	*great(t_node **token);
// t_node	*dless(t_node **token);
// t_node	*dgreat(t_node **token);
// t_node	*pipe(t_node **token);
// t_node	*new_line(t_node **token);
// t_node	*expand(t_node **token);
// t_node	*assign(t_node **token);

t_node	*parse_simple_command(t_node *token)
{
	if (!token)
		return (NULL);
	while (token)
	{
		if (token->type == 11 || token->type == 12 || token->type == 13)
			parse[token->type](&token);
		else
			token = token->next;
	}
	return (NULL);
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
