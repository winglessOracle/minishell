/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 14:22:25 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/05/12 12:34:24 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	read_heredoc(int *pipe, t_node *env_lst, t_node *input, t_smpl_cmd *cmd)
{
	char	*line_read;
	char	*line;
	t_node	*tokens;
	int		count;

	line = NULL;
	close(pipe[0]);
	count = 0;
	while (1)
	{
		line_read = get_input(env_lst, "PS2", 0);
		count ++;
		if (!ft_strcmp(line_read, input->content) || line_read == NULL)
		{
			if (line_read == NULL)
				ft_fprintf(2, "minishell: warning: here-document at line %d delimited by end-of-file (wanted '%s')\n", count, input->content);
			break ;
		}
		tokens = lexer(line_read, " \n");
		line = parse_heredoc(tokens, input, cmd);
		ft_putstr_fd(line, pipe[1]);
		free(line);
	}
	close(pipe[1]);
	exit(0);
}

int	here_doc(t_node *env_list, t_node *here_redirect, t_smpl_cmd *cmd)
{
	int		here_pipe[2];
	pid_t	pid;

	if (pipe(here_pipe) == -1)
		exit_error("pipe fail", errno);
	pid = fork();
	if (pid == -1)
		exit_error("fork fail", errno);
	if (!pid)
	{
		set_sigint_here();	
		read_heredoc(here_pipe, env_list, here_redirect, cmd);
	}
	wait(NULL);
	close(here_pipe[1]);
	return (here_pipe[0]);
}

void	get_heredocs(t_pipe *pipeline)
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
				tcmd->here_doc = \
					here_doc(pipeline->pipe_argv->env_list, tredirect, tcmd);
			}
			tredirect = tredirect->next;
		}
		tcmd = tcmd->next;
	}
}

int	merge_quoted_heredoc(t_node **token, t_smpl_cmd *cmd, int delim)
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
	split_and_remove_quotes(token, cmd, delim);
	return (0);
}

char	*parse_heredoc(t_node *token, t_node *here_redirect, t_smpl_cmd *cmd)
{
	int		type;
	char	*input;

	type = here_redirect->type;
	if (type == HEREDOC)
		type = INPUT;
	if (type == HEREDOCQ)
		type = HEREDOC;
	input = ft_strdup("");
	while (token)
	{
		token->type = check_token_content(token, token->type);
		if ((token->type == SQUOTE || token->type == DQUOTE) && type != HEREDOC)
			token->type = merge_quoted_heredoc(&token, cmd, -1);
		if (token->type == EXPAND && type != HEREDOC)
			token->type = expand(&token, cmd);
		if (token->content)
			input = ft_strjoin_free_s1(input, token->content);
		remove_node(&token, NULL);
	}
	input = ft_strjoin_free_s1(input, "\n");
	return (input);
}
