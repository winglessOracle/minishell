/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: carlo <carlo@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/06 15:16:31 by carlo         #+#    #+#                 */
/*   Updated: 2023/05/11 18:24:02 by cariencaljo   ########   odam.nl         */
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
void	check_cmd(char *cmd);
void	get_heredocs(t_pipe *pipeline);
void	assignments(t_smpl_cmd *pipe_argv, pid_t pid);
int		set_out(int *fd_pipe, t_node *temp);
void	set_in(int *keep, t_node *temp);
int		assign_one(t_pipe *pipeline);
int		set_fd(t_smpl_cmd *smpl_cmd, int *keep, int *fd_pipe);

#endif
