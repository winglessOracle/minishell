/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 14:22:25 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/04/05 13:01:13 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
// #include "lexer.h"

int	check_content(t_node **token, t_smpl_cmd *cmd)
{
	int	state;
	static function  *parse[7];

	parse[WORD] = add_word_to_cmd;
	parse[COMMENT] = remove_comment;
	parse[SQUOTE] = remove_squotes;
	parse[DQUOTE] = remove_dquotes;
	parse[EXPAND] = add_word_to_cmd;
	parse[ASSIGN] = add_word_to_cmd;
	printf("*CHECK CONTENT* %s\n", (*token)->content);
	while (*token && (*token)->type == WORD)
	{
		state = check_token_content(*token, (*token)->type);
		printf("state: %d\n", state);
		state = parse[state](token, cmd);
	}
	return(state);
}

int	redirect(t_node **tokens, t_smpl_cmd *cmd)
{
	printf("*REDIRECT* %s\n", (*tokens)->content);
	remove_node(tokens, cmd);
	return (0);
}

int	set_cmd_end(t_node **token, t_smpl_cmd *cmd)
{
	int check;

	printf("*CMD END* %s\n", (*token)->content);
	check = check_pipe(*token, cmd);
	remove_node(token, cmd);
	return (check);
}

t_node	*parse_smpl_cmd(t_node *tokens, t_smpl_cmd	**cmd)
{	
	int	state;
	static function  *parse[5];
	
	parse[WORD] = check_content;
	parse[BLANK] = remove_node;
	parse[REDIRECT] = redirect;
	parse[PIPE] = set_cmd_end;
	parse[NEW_LINE] = set_cmd_end;
	state = 0;
	while (tokens && !state)
		state = parse[tokens->type](&tokens, *cmd);
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
