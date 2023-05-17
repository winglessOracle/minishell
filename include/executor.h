/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: carlo <carlo@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/06 15:16:31 by carlo         #+#    #+#                 */
/*   Updated: 2023/05/16 09:06:36 by cwesseli      ########   odam.nl         */
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

void	executor(t_pipe *pipeline);
// checks
void	check_built(t_smpl_cmd *cmd);
int		check_builtins_curr_env(t_smpl_cmd *cmd);
void	check_cmd(char *cmd);
int		check_sorted_argv(t_node *argv);
int		check_and_pipe(t_pipe *pipeline, pid_t *pid, int *fd_pipe);
// init
void	fork_error(void);
int		init_keep(void);
pid_t	*init_pid(int argc);
// set
void	assignments(t_smpl_cmd *pipe_argv, pid_t pid);
int		set_out(int *fd_pipe, t_node *temp);
void	set_in(int *keep, t_node *temp);
int		set_fd(t_smpl_cmd *smpl_cmd, int *keep, int *fd_pipe);
// utils
char	**build_cmd_args(t_node **argv, int argc);
void	set_exit_st(int argc, pid_t *pid);
char	**get_env(t_node *env_list);
t_node	*sort_argv(t_node *argv);

#endif
