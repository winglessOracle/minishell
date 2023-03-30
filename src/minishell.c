/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 09:48:38 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/03/30 10:58:13 by carlo         ########   odam.nl         */
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
	add_variable(env_list, "PS1=CC_PROMPT:> ", 1);
	while (1)
	{
		if (line_read)
		{
		  	free(line_read);
		  	line_read = NULL;
		}
		rl_prompt = get_variable(env_list, "PS1");
		line_read = readline(rl_prompt);
		if (!ft_strcmp(line_read, "exit"))
			break ;
		if (line_read && *line_read)
		 	add_history(line_read);
		tokens = lexer(line_read, "|<> \t\n");

		//tests
		if (tokens)
		{
			run_tests(line_read, tokens, env_list);
			lstclear(&tokens, delete_content);
		}
	}
	//clear_history(); should be rl_clear_history() but that is not found?.
	exit(EXIT_SUCCESS);
}
