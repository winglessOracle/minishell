/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 09:48:38 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/04/21 11:14:51 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h" //test

void	leaks(void)
{
	system("leaks minishell -q");
}

int g_exit_status;

int	main(void)
{
	char		*line_read;
	t_node		*env_list;
	t_node		*tokens;
	t_pipe		*pipeline;

	//add max buffer?
	// atexit(leaks);
	env_list = init_env();
	read_history("log/history_log"); //remove
	while (1)
	{
		set_sig_term();
		line_read = get_input(env_list, "PS1", 1);
		write_history("log/history_log"); //remove
		tokens = lexer(line_read, "|<> \t\n");
	// print_tokens(tokens, "CREATED TOKENS\n");
		while (tokens)
		{
			pipeline = parse_pipeline(&tokens, env_list);
	// printf("CREATED PIPLINE\n");
	// print_pipeline(pipeline);
			executor(pipeline);
			printf("g_exit_status main=%d\n", g_exit_status);
	// printf("PASSED EXECUTOR\n");
	// printf("exitstatus=%d\n", exitstatus);
		}
	}
	rl_clear_history();
	execute_exit(NULL, env_list);
}
