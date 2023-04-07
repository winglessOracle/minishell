/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 14:22:25 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/04/07 10:25:57 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
// #include "lexer.h"

int	set_cmd_end(t_node **token, t_smpl_cmd *cmd)
{
	int	check;

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
		if (str[i] == '\"' && type != SQUOTE)
			return (DQUOTE);
		else if (str[i] == '\'' && type != DQUOTE)
			return (SQUOTE);
		else if (str[i] == '$' && str[i + 1] != ' ' &&  \
					str[i + 1] != '\0' && type != SQUOTE)
			return (EXPAND);
		else if (str[i] == '=' && type != DQUOTE && type != SQUOTE)
			return (ASSIGN);
		i++;
	}
	return (WORD);
}

int	expand_token(t_node **token, t_smpl_cmd *cmd)
{
	int					state;
	static t_function	*parse[10];

	parse[WORD] = add_word_to_cmd;
	parse[COMMENT] = remove_comment;
	parse[SQUOTE] = remove_squotes;
	parse[DQUOTE] = remove_dquotes;
	parse[EXPAND] = expand;
	parse[ASSIGN] = parser_assign; // nu in linked list for later processing (is shell variable so technically out of scope?)
	// printf("*CHECK CONTENT* %s\n", (*token)->content);
	while (*token && (*token)->type == WORD)
	{
		state = check_token_content(*token, (*token)->type);
		state = parse[state](token, cmd);
	}
	return (state);
}

t_node	*parse_smpl_cmd(t_node *tokens, t_smpl_cmd	**cmd)
{	
	int					state;
	static t_function	*parse[5];

	parse[WORD] = expand_token;
	parse[BLANK] = remove_node;
	parse[REDIRECT] = get_redirect;
	parse[PIPE] = set_cmd_end;
	parse[NEW_LINE] = set_cmd_end;
	state = 0;
	while (tokens && !state)
		state = parse[tokens->type](&tokens, *cmd);
	if (state == -1)
		printf("error msg?\n");
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
		if (cmd)
		{
			lstadd_back_pipe(&(*pipeline)->pipe_argv, cmd);
			(*pipeline)->pipe_argc++;
		}
		else
			return (tokens);
	}
	return (tokens);
}
