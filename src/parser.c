/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 14:22:25 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/04/04 15:19:45 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

t_node	*parse_smpl_cmd(t_node *tokens, t_smpl_cmd	**cmd)
{	
	int	state;
	static function  *parse[MAX_TYPE] = {
		set_type_word, //word
		set_type_word, //dquote
		set_type_word, //squote
		todo, //expand
		todo, //assign
		redirect_output, //great
		redirect_input, //less
		set_here_end, //dless
		set_append, //dgreat
		set_cmd_end, //pipe
		set_cmd_end, //new_line
		remove_node, //comment
		remove_node, //space
		remove_node, //tab
		NULL, //name
	};
	
	state = 0;
	while (tokens && !state)
	{
		if (!(tokens->type == WORD || tokens->type == NAME))
			state = parse[tokens->type](&tokens, *cmd);
		else
		{
			lstadd_back(&(*cmd)->cmd_argv, lstpop(&tokens));
			(*cmd)->cmd_argc++;
		}
	}
	if (state == -1)
		*cmd = NULL;
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
		tokens = parse_smpl_cmd(tokens, &cmd);
		if (!cmd)
			return (NULL);
		lstadd_back_pipe(&pipeline->pipe_argv, cmd);
		pipeline->pipe_argc++;
	}
	return (pipeline);
}

// done if COMMENT || SPACE || TAB -> remove?
// if LESS -> check next and set input 
// if GREAT -> check next and set output TRUNC
// if DLESS -> io_here (set value next node in master_struct?)
// if DGREAT -> check next set output append
// done if PIPE -> end simple command
// done if NEW_LINE -> end simple command and pipeline
// if EXPAND -> expand to (env)value
	// if $? -> expand to last exit status
// if ASSIGN -> assign variable
