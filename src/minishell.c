/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 09:48:38 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/04/26 18:15:43 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "builtin.h" //test

void	leaks(void)
{
	system("leaks minishell -q");
}

int	g_exit_status;

int	main(void)
{
	char		*line_read;
	t_node		*env_list;
	t_node		*tokens;

	//add max buffer?
	// atexit(leaks);
	env_list = init_env();
	read_history("log/history_log"); //remove
	// set_signals();
	while (1)
	{
		line_read = get_input(env_list, "PS1", 1);
		if (line_read == NULL)
			exit_sig(env_list);
		write_history("log/history_log"); //remove
		tokens = lexer(line_read, LEXER_SPLIT);
		parse_and_execute(tokens, env_list);
	}
	rl_clear_history();
	execute_exit(NULL, env_list);
	return (0);
}
