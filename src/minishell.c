/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 09:48:38 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/03/28 18:22:23 by carlo         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp) //remove arguments and return type?
{
	t_node		**tokens;
	t_master	*master;
	char		*line_read;
	
	(void)argc;
	(void)argv;
	//atexit(leaks);
	line_read = NULL;
	master = init_master_struct();
	master->env_list = env_to_list(envp);
	// master->commands =
	add_variable(master->env_list, "PS1=CC_PROMPT:> ", 1);
	
	while (1)
	{
		if (line_read)
		{
		  	free(line_read);
		  	line_read = NULL;
		}
		line_read = readline("CC_PROMPT:$> ");
		if (!ft_strcmp(line_read, "exit"))
			break ;
		if (line_read && *line_read)
		 	add_history(line_read);
		//tokens = lexer(line_read, "|<> \t");
		//lstclear(tokens, delete_content);
	}
	//tests
		run_tests(tokens, master);
	//rl_clear_history();
	exit(EXIT_SUCCESS);
}
