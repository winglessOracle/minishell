/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 14:22:25 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/05/11 09:58:45 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int	here_doc(t_pipe *pipeline, t_node *here_redirect, t_smpl_cmd *cmd)
{
	int		here_pipe[2];
	char	*line_read;
	char	*line;
	t_node	*tokens;
	pid_t	pid;

	line = NULL;
	if (pipe(here_pipe) == -1)
		exit_error("pipe fail", errno);
	pid = fork();
	if (pid == -1)
		exit_error("fork fail", errno);
	if (!pid)
	{
		close(here_pipe[0]);
		while (1)
		{
			line_read = get_input(pipeline->pipe_argv->env_list, "PS2", 0);
			if (!ft_strcmp(line_read, here_redirect->content) || line_read == NULL)
				break ;
			tokens = lexer(line_read, " \n");
			line = parse_heredoc(tokens, here_redirect, cmd);
			ft_putstr_fd(line, here_pipe[1]);
			free(line);
		}
		close(here_pipe[1]);
		exit(0);
	}
	wait(NULL);
	close(here_pipe[1]);
	return (here_pipe[0]);
}

void	read_heredocs(t_pipe *pipeline)
{
	t_smpl_cmd	*tcmd;
	t_node		*tredirect;

	tcmd = pipeline->pipe_argv;
	while (tcmd)
	{
		tredirect = tcmd->redirect;
		while (tredirect)
		{
			if (tredirect->type == HEREDOC || tredirect->type == HEREDOCQ)
			{
				if (tcmd->here_doc)
					close(tcmd->here_doc);
				tcmd->here_doc = here_doc(pipeline, tredirect, tcmd);
			}
			tredirect = tredirect->next;
		}
		tcmd = tcmd->next;
	}
}

int	split_and_remove_quotes_delim(t_node **tokens, t_smpl_cmd *cmd)
{
	t_node	*words;
	char	*content;
	char	quote;
	char	quote_open;

	quote = get_quote_char((*tokens)->type);
	content = ft_strdup("");
	words = split_to_list((*tokens)->content, "\'\" ");
	while (words)
	{
		if (words->content[0] == quote)
		{
			quote_open = 1;
			remove_node(&words, cmd);
		}
		while (words && words->content[0] != quote)
		{
			if (words->content)
				content = ft_strjoin_free_s1(content, words->content);
			remove_node(&words, cmd);
		}
		if (words && words->content[0] == quote && quote_open)
		{
			quote_open = 0;
			remove_node(&words, cmd);
		}
	}
	free((*tokens)->content);
	(*tokens)->content = content;
	return (0);
}

int	merge_quoted_heredocdelim(t_node **token, t_smpl_cmd *cmd)
{
	int		type;
	char	quote;

	type = (*token)->type;
	quote = get_quote_char((*token)->type);
	while (*token && (*token)->next)
	{
		if (!(count_quotes((*token)->content, quote) % 2))
			break ;
		merge_tokens(*token, type);
	}
	if (*token && count_quotes((*token)->content, quote) % 2)
		return (0);
	split_and_remove_quotes_delim(token, cmd);
	return (0);
}

int	merge_quoted_heredoc(t_node **token, t_smpl_cmd *cmd)
{
	int		type;
	char	quote;

	type = (*token)->type;
	quote = get_quote_char((*token)->type);
	while (*token && (*token)->next)
	{
		if (!(count_quotes((*token)->content, quote) % 2))
			break ;
		merge_tokens(*token, type);
	}
	if (*token && count_quotes((*token)->content, quote) % 2)
		return (0);
	split_and_remove_quotes(token, cmd);
	return (0);
}