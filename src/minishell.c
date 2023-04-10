/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 09:48:38 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/04/10 15:06:55 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	leaks(void)
{
	system("leaks minishell -q");
}

int	main(void)
{
	char		*line_read;
	t_node		*env_list;
	t_node		*tokens;
	t_pipe		*pipeline;

	// atexit(leaks);
	line_read = NULL;
	env_list = init_env();
	set_sig_term();
	read_history("log/history_log"); //remove?
	while (1)
	{
		line_read = readline(get_variable(env_list, "PS1"));
		if (!ft_strcmp(line_read, "exit"))  // is built in so can be removed after that works
			break ;
		if (line_read)
			add_history(line_read);
	printf("READ INPUT\n");
		write_history("log/history_log"); //remove?
		tokens = lexer(line_read, "|<> \t\n");
	printf("CREATED TOKENS\n");
	while (tokens)
	{
		pipeline = parse_pipeline(&tokens, env_list);
		(void)pipeline; // execute pipeline
	}
	printf("END OF INPUT\n");
	}
	rl_clear_history();
	exit(EXIT_SUCCESS);
}
