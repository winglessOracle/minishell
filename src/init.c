/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/24 13:05:51 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/03/29 15:40:41 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_smpl_cmd	*init_smpl_cmd()
{
	t_smpl_cmd	*cmd;

	cmd = malloc(sizeof(t_smpl_cmd));
	if (!cmd)
		exit_error(errno);
	ft_memset(cmd, 0, sizeof(t_smpl_cmd));
	return (cmd);
}