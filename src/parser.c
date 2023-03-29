/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 14:22:25 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/03/29 22:19:29 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int		todo(t_node **token)
{
	printf("not handeled yet: type: %d, content: %s\n", (*token)->type, (*token)->content);
	(*token) = (*token)->next;
	return (0);
}

int	set_type_word(t_node **token)
{
	(*token)->type = WORD;
	return (0);
}

int	set_cmd_end(t_node **token)
{
	lstdelone(*token, delete_content);
	return (1);
}

t_smpl_cmd	*parse_smpl_cmd(t_node *tokens, t_smpl_cmd	*cmd)
{	
	int	state;
	
	state = 0;
	while (tokens && state == 0)
	{
		if (tokens->type == WORD)
		{
			lstadd_back(&cmd->cmd_argv, lstpop(&tokens));
			cmd->cmd_argc++;
		} 
		else
			state = parse[tokens->type](&tokens);
		if (state == -1)
			return (NULL);
	}
	return (cmd);
}

t_pipe	*parse_pipeline(t_node *tokens, t_node *env_list)
{	
	t_smpl_cmd	*cmd;
	t_pipe		*pipeline;
	
	if (!tokens)
		return (NULL);
	pipeline = init_pipeline();
	if (tokens) //should be while when all tokens are parsed correctly
	{
		cmd = parse_smpl_cmd(tokens, init_smpl_cmd(env_list));
		if (!cmd)
			return (NULL);
		print_cmd(cmd);		// test
		lstadd_back_pipe(&pipeline->pipe_argv, cmd);
		pipeline->pipe_argc++;
	}
	return (pipeline);
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
