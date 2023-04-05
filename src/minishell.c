/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 09:48:38 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/04/04 17:39:56 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	leaks(void)
{
	system("leaks minishell -q");	
}

int	main(void)
{
	t_node		*tokens;
	t_node		*env_list;
	t_pipe		*pipeline;
	char		*line_read;
	char		*prompt;

	// atexit(leaks);
	line_read = NULL;
	env_list = init_env();
	set_sig_term();
	read_history("log/history_log"); //remove?
	while (1)
	{
		prompt = get_variable(env_list, "PS1");
		line_read = readline(prompt); // line is freed in lexer after processing
		if (!ft_strcmp(line_read, "exit"))
			break ;
		if (line_read)
		 	add_history(line_read);
	printf("READ INPUT\n");
		tokens = lexer(line_read, "|<> \t\n");
	printf("MERGED TOKENS\n");
	// print_tokens(tokens);
		pipeline = parse_pipeline(tokens, env_list);
	printf("CREATED PIPLINE\n");
	print_pipeline(pipeline);
	free(prompt);
	}
	write_history("log/history_log"); //remove?
	rl_clear_history();
	exit(EXIT_SUCCESS);
}
