/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 09:48:38 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/04/25 10:49:46 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
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
	t_list		*list;

	//add max buffer?
	// atexit(leaks);
	env_list = init_env();
	read_history("log/history_log"); //remove
	set_signals();
	while (1)
	{
		line_read = get_input(env_list, "PS1", 1);
		if (line_read == NULL)
			exit_sig(env_list);
		write_history("log/history_log"); //remove
		tokens = lexer(line_read, LEXER_SPLIT);
		list = init_list();
		while (tokens)
		{
			// printf("\n\nlist state: %d, list type: %d\n", list->state, list->type);
			// print_tokens(tokens, "before pipeline\n");
			pipeline = parse_pipeline(&tokens, env_list, list);
			// printf("pipeline\n");
			// print_pipeline(pipeline);
			if (pipeline)
				executor(pipeline);
			check_list(&tokens, list);
			list->type = 0;
		}
	}
	rl_clear_history();
	execute_exit(NULL, env_list);
	return (0);
}
