/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/24 13:05:51 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/03/29 09:51:46 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_master	*init_master_struct(void)
{
	t_master *master;
	
	master = malloc(sizeof(t_master));
	if (!master)
		exit_error(errno);
	master->infile = NULL;
	master->outfile = NULL;
	master->errfile = NULL;
	master->here_end = NULL;
	master->last_exit = 0;
	return (master);
}