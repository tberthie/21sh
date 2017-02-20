/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_launch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 19:56:04 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/20 19:56:05 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "sh.h"
#include "error.h"
#include "builtins.h"

#include <stdlib.h>

void	launch_cmd(t_exec *exec)
{
	free(treat_redirs(exec->redirs[exec->id]));
	if (!*exec->paths[exec->id])
	{
		builtins(exec->args[exec->id]);
		exit(g_sh.last_ret);
	}
	execve(exec->paths[exec->id], exec->args[exec->id], g_sh.env);
	error("binary format error", *exec->args[exec->id]);
	exit(126);
}
