/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 14:22:25 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/04/05 18:30:01 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
// #include "lexer.h"

int	set_cmd_end(t_node **token, t_smpl_cmd *cmd)
{
	int check;

	check = check_pipe(*token, cmd);
	if ((*token)->type == PIPE)
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
	static function  *parse[6];

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
	{
		while (tokens && tokens->type != NEW_LINE)
			remove_node(&tokens, *cmd);
		*cmd = NULL;
	}
	return (tokens);
}

t_node	*parse_pipeline(t_node *tokens, t_node *env_list, t_pipe **pipeline)
{	
	t_smpl_cmd	*cmd;
	
	if (!tokens)
		return (NULL);
	while (tokens)
	{
		cmd = init_smpl_cmd(env_list);
		tokens = parse_smpl_cmd(tokens, &cmd);
		if (tokens && tokens->type == NEW_LINE)
		{
			remove_node(&tokens, cmd);
			return (tokens);
		}
		if (!cmd)
		{
			*pipeline = NULL;
			if (tokens && tokens->type == NEW_LINE)
				remove_node(&tokens, cmd);
			return (tokens);
		}
		lstadd_back_pipe(&(*pipeline)->pipe_argv, cmd);
		(*pipeline)->pipe_argc++;
	}
	return (tokens);
}

