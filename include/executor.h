/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: carlo <carlo@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/06 15:16:31 by carlo         #+#    #+#                 */
/*   Updated: 2023/04/25 21:45:52 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include "parser.h"
# include "builtin.h"

typedef int	t_built(char **, t_node *);

#endif