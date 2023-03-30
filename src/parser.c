/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 14:22:25 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/03/30 16:12:30 by cariencaljo   ########   odam.nl         */
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
	t_node	*temp;
	
	if (!*token)
		return (-1);
	temp = lstpop(token);
	lstdelone(temp, delete_content);
	return (0);
}

int	set_type_word(t_node **token, t_smpl_cmd *cmd)
{
	(*token)->type = WORD;
	return (0);
}

int	set_cmd_end(t_node **token, t_smpl_cmd *cmd)
{
	remove_node(token, cmd);
	return (1);
}

t_node	*parse_smpl_cmd(t_node *tokens, t_smpl_cmd	*cmd)
{	
	int	state;
	static function  *parse[MAX_TYPE] = {
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
			state = parse[tokens->type](&tokens, cmd);
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
