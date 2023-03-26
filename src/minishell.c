/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 09:48:38 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/03/26 22:18:03 by carlo         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp) //remove arguments and return type?
{
	(void)argc;
	(void)argv;
	char	*command_buff;
	t_node **tokens;
	t_master *master;

	master = init_master_struct();
	// master->commands =
	master->env_list = env_to_list(envp);
	while (1)
	{
		command_buff = readline("CC_PROMPT:$> ");
		if (!ft_strcmp(command_buff, "exit"))
			break ;
		if (ft_strlen(command_buff) > 0)
			add_history(command_buff);
		tokens = lexer(command_buff, "|&;()<> \t");
	}

	//tests
	run_tests(command_buff, tokens, master);
	
		exit(EXIT_SUCCESS);
}
