/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 09:48:38 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/04/18 12:37:29 by cwesseli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h" //test

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
	int			exitstatus;

	//add max buffer?
	// atexit(leaks);
	env_list = init_env();
	set_sig_term();
	read_history("log/history_log"); //remove
	while (1)
	{
		line_read = get_input(env_list, "PS1");
		write_history("log/history_log"); //remove
		tokens = lexer(line_read, "|<> \t\n");
	// print_tokens(tokens, "CREATED TOKENS\n");
		while (tokens)
		{
			pipeline = parse_pipeline(&tokens, env_list);
	//print_pipeline(pipeline);

			exitstatus = executor(pipeline);
			
	// printf("CREATED PIPLINE\n");
	// (void)exitstatus;
	// printf("PASSED EXECUTOR\n");
	// printf("exitstatus=%d\n", exitstatus);
		}
	}
	rl_clear_history();
	execute_exit(NULL, env_list);
}
