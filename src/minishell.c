/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 09:48:38 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/03/27 19:12:19 by cwesseli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp) //remove arguments and return type?
{
	char		*line_read;
	t_node		**tokens;
	t_master	*master;

	(void)argc;
	(void)argv;
	master = init_master_struct();
	master->env_list = env_to_list(envp);
	add_variable(master->env_list, "PS1=CC_PROMPT:> ", 1);
	//master->commands =
	line_read = NULL;	
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
		tokens = lexer(line_read, "|&;()<> \t");
	}

	//tests
	run_tests(tokens, master);
	//clear_history(); // reaserch
	exit(EXIT_SUCCESS);
}
