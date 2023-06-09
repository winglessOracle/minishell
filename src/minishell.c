/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 09:48:38 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/05/29 13:12:59 by cwesseli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "builtin.h"

int	g_exit_status;

char	*get_input(t_node *env_list, char *var, int history)
{
	char		*prompt;
	char		*line_read;

	line_read = NULL;
	prompt = get_variable(env_list, var);
	line_read = readline(prompt);
	if (line_read && ft_strlen(line_read) > MAX_INPUT_LEN)
	{
		printf("Input exceeds max length of %d characters\n", MAX_INPUT_LEN);
		line_read = ft_strdup("");
	}
	if (line_read && history)
		add_history(line_read);
	free(prompt);
	return (line_read);
}

int	main(void)
{
	char		*line_read;
	t_node		*env_list;
	t_node		*tokens;

	env_list = init_env();
	read_history("log/history_log");
	while (1)
	{
		set_signals();
		line_read = get_input(env_list, "PS1", 1);
		if (line_read == NULL)
			exit_sig(env_list);
		if (ft_strlen(line_read) > 0)
			write_history("log/history_log");
		tokens = lexer(line_read, LEXER_SPLIT);
		parse_and_execute(tokens, env_list);
	}
	rl_clear_history();
	execute_exit(NULL, env_list);
	return (0);
}
