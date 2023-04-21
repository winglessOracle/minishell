/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 14:22:25 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/04/20 21:27:04 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "builtin.h"

int	check_assign(char *str, int type)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' && type != DQUOTE && type != SQUOTE)
			return (ASSIGN);
		i++;
	}
	return (WORD);
}

int	check_token_content(t_node *token, int type) // refactor when tester available
{
	char	*str;
	int		i;

	i = 0;
	if (!token->content)
		return (WORD);
	str = token->content;
	if (str[0] == '#' && type != DQUOTE && type != SQUOTE)
		return (COMMENT);
	if (str[0] == '~' && (str[1] == '/' || str[1] == '\0') \
								&& type != DQUOTE && type != SQUOTE) // can remove DQUOTE and SQUOTE?
		return (TILDE);
	while (str[i])
	{
		if (str[i] == '\"' && type != SQUOTE)
			return (DQUOTE);
		else if (str[i] == '\'' && type != DQUOTE)
			return (SQUOTE);
		else if (str[i] == '$' && str[i + 1] != ' ' && \
					str[i + 1] != '\0' && type != SQUOTE && type != DQUOTE)
			return (EXPAND);
		if (str[i] == '=' && type != DQUOTE && type != SQUOTE \
												&& token->type != ASSIGN_T)  //// can remove DQUOTE and SQUOTE?
			return (ASSIGN_T);
		i++;
	}
	return (check_assign(str, type));
}

int	parse_cmd(t_node **tokens, t_smpl_cmd **cmd)
{	
	int					state;
	static t_function	*parse[5];

	parse[WORD] = expander;
	parse[BLANK] = remove_node;
	parse[REDIRECT] = redirect_tokens;
	parse[PIPE] = set_cmd_end;
	parse[NEW_LINE] = set_cmd_end;
	state = 0;
	while (*tokens && !state)
		state = parse[(*tokens)->type](tokens, *cmd);
	state = set_cmd_end(tokens, *cmd);
	check_env(*cmd);
	return (state);
}

t_pipe	*parse_pipeline(t_node **tokens, t_node *env_list)
{	
	t_pipe		*pipeline;
	t_smpl_cmd	*cmd;
	int			state;

	state = 0;
	pipeline = init_pipeline();
	while (*tokens && state != -1)
	{
		cmd = init_smpl_cmd(env_list);
		state = parse_cmd(tokens, &cmd);
		if (cmd)
		{
			lstadd_back_cmd(&pipeline->pipe_argv, cmd);
			pipeline->pipe_argc++;
		}
		if (state == -1)
			lstclear_cmdlst(&pipeline->pipe_argv, delete_cmd);
		if (*tokens && (*tokens)->type == NEW_LINE)
		{
			state = remove_node(tokens, NULL);
			break ;
		}
	}
	return (pipeline);
}

char	*parse_heredoc(t_node *token, t_smpl_cmd *cmd)
{
	int					type;
	int					state;
	char				*input;

	type = cmd->redirect->type;
	if (type == HEREDOC)
		type = INPUT;
	if (type == HEREDOCQ)
		type = HEREDOC;
	input = ft_strdup("");
	while (token)
	{
		token->type = type;
		state = check_token_content(token, token->type);
		if ((state == SQUOTE || state == DQUOTE) && type != HEREDOC)
			state = remove_quotes(&token, cmd);
		else if (state == EXPAND && type != HEREDOC)
			state = expand(&token, cmd);
		state = check_token_content(token, token->type);
		if (token->content)
			input = ft_strjoin_free_s1(input, token->content);
		remove_node(&token, NULL);
	}
	input = ft_strjoin_free_s1(input, "\n");
	return (input);
}
