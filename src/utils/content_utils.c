/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   content_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/05 11:06:10 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/04/05 13:04:26 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// #include "lexer.h"
#include "parser.h"

int	check_quotes(int nr_quotes)
{
	if ((nr_quotes % 2) != 0)
	{
		write(2, "Input error, unclosed quotes\n", 29);
		return (-1);
	}
	else
		return (0);
}

int	add_word_to_cmd(t_node **token, t_smpl_cmd *cmd)
{
	printf("*WORD* %s\n", (*token)->content);
	lstadd_back(&cmd->cmd_argv, lstpop(token));
	cmd->cmd_argc++;
	return (0);
}

int	remove_comment(t_node **token, t_smpl_cmd *cmd)
{
	while (*token && (*token)->type != NEW_LINE)
	{
		printf("*REMOVE COMMENT* %s\n", (*token)->content);	
		remove_node(token, cmd);
	}
	return (0);
}

int	remove_squotes(t_node **token, t_smpl_cmd *cmd)
{
	int		nr_quotes;
	char	*content;
	char	*temp;
	t_node	*words;
	
	nr_quotes = 0;
	content = NULL;
	while (*token)
	{
		temp = content;
		words = split_to_list((*token)->content, "\'");
		remove_node(token, cmd);
		while (words)
		{
			if (words->content[0] == '\'')
				nr_quotes += 1;
			else
			{
				if (temp)
				{
					content = ft_strjoin(temp, words->content);
					free(temp);
				}
				else
					content = ft_strdup(words->content);
			}
			remove_node(&words, cmd);
		}
		if ((nr_quotes % 2) == 0)
			break;
	}
	printf("*SQUOTED SEQUENCE* %s\n", content);
	lstadd_back(&cmd->cmd_argv, new_node(SQUOTE, content));
	cmd->cmd_argc++;
	return (check_quotes(nr_quotes));
}

int	remove_dquotes(t_node **token, t_smpl_cmd *cmd)
{
	int		nr_quotes;
	char	*content;
	char	*temp;
	t_node	*words;
	
	nr_quotes = 0;
	content = NULL;
	while (*token)
	{
		temp = content;
		words = split_to_list((*token)->content, "\"");
		remove_node(token, cmd);
		while (words)
		{
			if (words->content[0] == '\"')
				nr_quotes += 1;
			else
			{
				if (temp)
				{
					content = ft_strjoin(temp, words->content);
					free(temp);
				}
				else
					content = ft_strdup(words->content);
			}
			remove_node(&words, cmd);
		}
		if ((nr_quotes % 2) == 0)
			break;
	}
	printf("*DQUOTED SEQUENCE* %s\n", content);
	words = new_node(DQUOTE, content);
	words->type = check_token_content(words, words->type);
	lstadd_back(&cmd->cmd_argv, words);
	cmd->cmd_argc++;
	return (check_quotes(nr_quotes));
}
