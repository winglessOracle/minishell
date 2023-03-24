/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cwesseli <cwesseli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 09:48:38 by cwesseli      #+#    #+#                 */
/*   Updated: 2023/03/24 14:05:55 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc; //waarom is dit?
	(void)argv;
	t_node **tokens;
	t_master *master;

	char *str = "'Hello' world>>How| are$YOU|> to||day?";
	tokens = malloc(sizeof(t_node **)); 
	if (!tokens)
		exit_error(21);
	*tokens = NULL;
	lexer(tokens, str, "|&;()<> \t");  // eventueel de malloc toch veplaatsen naar binnen de lexer? Dan is in main alleen de declaration  en dan 'token = lexer()'
	master = init_master_struct();
	master->env_list = env_to_list(envp);
	// master->commands =

	//tests
	run_tests(str, tokens, master);
	
	exit(EXIT_SUCCESS);
}
