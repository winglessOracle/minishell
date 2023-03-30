/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 14:22:25 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/03/30 11:56:44 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int		todo(t_node **token)
{
	printf("not handeled yet: type: %d, content: %s\n", (*token)->type, (*token)->content);
	(*token) = (*token)->next;
	remove_node(token);
	return (0);
}

int	set_type_word(t_node **token)
{
	(*token)->type = WORD;
	return (0);
}

int	set_cmd_end(t_node **token)
{
	remove_node(token);
	return (1);
}

t_node	*parse_smpl_cmd(t_node *tokens, t_smpl_cmd	*cmd)
{	
	int	state;
	static function  *parse[14] = {
		NULL, //word
		set_type_word, //dquote
		set_type_word, //squote
		todo, //expand
		todo, //assign
		todo, //great
		todo, //less
		todo, //dless
		todo, //dgreat
		set_cmd_end, //pipe
		set_cmd_end, //new_line should this do more?
		remove_node, //comment
		remove_node, //space
		remove_node, //tab
	};
	
	state = 0;
	while (tokens && !state)
	{
		if (tokens->type == WORD)
		{
			lstadd_back(&cmd->cmd_argv, lstpop(&tokens));
			cmd->cmd_argc++;
		} 
		else
			state = parse[tokens->type](&tokens);
	}
	if (state == -1)
		return (NULL);
	return (tokens);
}

t_pipe	*parse_pipeline(t_node *tokens, t_node *env_list)
{	
	t_smpl_cmd	*cmd;
	t_pipe		*pipeline;
	
	if (!tokens)
		return (NULL);
	pipeline = init_pipeline();
	while (tokens)
	{
		cmd = init_smpl_cmd(env_list);
		tokens = parse_smpl_cmd(tokens, cmd);
		if (!cmd)
			return (NULL);
		lstadd_back_pipe(&pipeline->pipe_argv, cmd);
		pipeline->pipe_argc++;
	}
	// test
	print_pipeline(pipeline);
	print_tokens(tokens);
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
