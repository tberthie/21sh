/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_launch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 16:29:11 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/28 16:29:11 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "sh.h"
#include "error.h"
#include "builtins.h"

#include <stdlib.h>

void	launch_cmd(t_exec *exec)
{
	treat_redirs(exec->redirs[exec->id], 0);
	if (!*exec->paths[exec->id])
	{
		builtins(exec->args[exec->id]);
		exit(g_sh.last_ret);
	}
	execve(exec->paths[exec->id], exec->args[exec->id], g_sh.env);
	error("binary format error", *exec->args[exec->id]);
	exit(126);
}
