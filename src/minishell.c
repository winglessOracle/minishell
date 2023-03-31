/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 09:48:38 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/03/31 10:19:47 by cwesseli      ########   odam.nl         */
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
	master = init_master_struct();
	master->env_list = env_to_list(envp);
	add_variable(master->env_list, "PS1=CC_PROMPT:>", 1);
	add_variable(master->env_list, "PS2=", 1);
	while (1)
	{
		//add siganal initializer add flag restart for certain strings
		
		if (line_read)
		{
		  	free(line_read);
		  	line_read = NULL;
		}
		line_read = readline(get_variable(master->env_list, "PS1"));
		if (!ft_strcmp(line_read, "exit"))
			break ;
		if (line_read && *line_read)
		 	add_history(line_read);
		tokens = lexer(line_read, "|<> \t\n");

		// tests
		run_tests(line_read, tokens, master);
	
		// if (tokens)
		//	lstclear(&tokens, delete_content);
	}
	//clear_history(); should be rl_clear_history() but that is not found?.
	exit(EXIT_SUCCESS);
}
