/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 14:22:25 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/04/05 16:35:23 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
// #include "lexer.h"

int	set_cmd_end(t_node **token, t_smpl_cmd *cmd)
{
	int check;

	check = check_pipe(*token, cmd);
	remove_node(token, cmd);
	return (check);
}

int	check_token_content(t_node *token, int type)
{
	char	*str;
	int		i;

	i = 0;
	str = token->content;
	if (str[0] == '#' && type != DQUOTE && type != SQUOTE)
		return (COMMENT);
	while (str[i])
	{
		if (str[i]== '\"' && type != SQUOTE)
			return (DQUOTE);
		else if (str[i] == '\'' && type != DQUOTE)
			return (SQUOTE);
		else if (str[i] == '$' && type != SQUOTE)
			return (EXPAND);
		else if (str[i] == '=' && type != DQUOTE && type != SQUOTE)
			return (ASSIGN);
		i++;
	}
	return (WORD);
}

int	check_token(t_node **token, t_smpl_cmd *cmd)
{
	int	state;
	static function  *parse[7];

	parse[WORD] = add_word_to_cmd;
	parse[COMMENT] = remove_comment;
	parse[SQUOTE] = remove_squotes;
	parse[DQUOTE] = remove_dquotes;
	parse[EXPAND] = expand;
	parse[ASSIGN] = assign; // hoe weet je nu welke var dit was als er later export uitgevoerd moet worden.. ? niet hier doen?
	// printf("*CHECK CONTENT* %s\n", (*token)->content);
	while (*token && (*token)->type == WORD)
	{
		state = check_token_content(*token, (*token)->type);
		// printf("state: %d\n", state);
		state = parse[state](token, cmd);
	}
	return(state);
}

t_node	*parse_smpl_cmd(t_node *tokens, t_smpl_cmd	**cmd)
{	
	int	state;
	static function  *parse[5];
	
	parse[WORD] = check_token;
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

