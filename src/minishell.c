/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 09:48:38 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/04/11 13:02:29 by cariencaljo   ########   odam.nl         */
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

	atexit(leaks);
	env_list = init_env();
	set_sig_term();
	read_history("log/history_log"); //remove?
	while (1)
	{
		line_read = get_input(env_list, "PS1");
		write_history("log/history_log"); //remove?
	// is exit built-in so can be removed after that works
		if (!ft_strcmp(line_read, "exit"))  
			break ;
	printf("READ INPUT\n");
		tokens = lexer(line_read, "|<> \t\n");
	printf("CREATED TOKENS\n");
	// print_tokens(tokens, "CREATED TOKENS\n");
	while (tokens)
	{
		pipeline = parse_pipeline(&tokens, env_list);
	printf("CREATED PIPLINE\n");
		delete_pipe(pipeline);
	// print_pipeline(pipeline);
	}
	printf("END OF INPUT\n");
	}
	rl_clear_history();
	exit(get_exit(env_list));
}
