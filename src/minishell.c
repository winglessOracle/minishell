/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 09:48:38 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/03/31 12:30:44 by cwesseli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp) //remove arguments and return type?
{
	t_node		*tokens;
	t_node		*env_list;
	char		*line_read;

	(void)argc;
	(void)argv;
	atexit(leaks);
	line_read = NULL;
	env_list = env_to_list(envp);
	init_variables(env_list);

	while (1)
	{
		// add siganal initializer add flag restart for certain strings
		set_signals();
		if (line_read)
		{
		  	free(line_read);
		  	line_read = NULL;
		}
		line_read = readline(get_variable(env_list, "PS1")); //still does not return nl as intended
		if (!ft_strcmp(line_read, "exit"))
			break ;
		if (line_read && *line_read)
		 	add_history(line_read);
		tokens = lexer(line_read, "|<> \t\n");

		// tests
		run_tests(line_read, tokens, env_list);
		if (tokens)
			lstclear(&tokens, delete_content);
	}
	//clear_history(); should be rl_clear_history() but that is not found?.
	exit(EXIT_SUCCESS);
}
