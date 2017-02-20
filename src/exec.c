/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 19:55:50 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/20 19:55:52 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "error.h"
#include "builtins.h"
#include "sh.h"

#include "libft.h"

#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

static void		treat_wait(char *bin)
{
	int		status;

	wait(&status);
	if (WIFEXITED(status))
		g_sh.last_ret = WEXITSTATUS(status);
	else
		print_exit_signal((g_sh.last_ret = 128 + WTERMSIG(status)), bin);
}

static void		exec_simple(t_exec *exec)
{
	pid_t	ret;
	int		**fds;

	if (!**exec->paths)
	{
		fds = treat_redirs(*exec->redirs);
		builtins(*exec->args);
		restore_redirs(fds);
	}
	else if (!(ret = fork()))
		launch_cmd(exec);
	else if (ret != -1)
		treat_wait(**exec->args);
	else
		error("fork failed", (char*)0);
}

void			exec(t_exec *exec)
{
	if ((exec->paths = find_exec_paths(exec->args)))
	{
		exec_pre_conf();
		if (exec->args[1])
			exec_pipes(exec);
		else
			exec_simple(exec);
		ft_parrfree((void**)exec->paths);
		exec_post_conf();
	}
}
