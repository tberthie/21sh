/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfontani <tfontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 14:26:54 by tfontani          #+#    #+#             */
/*   Updated: 2017/02/24 12:51:21 by tfontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "sh.h"
#include "error.h"
#include "builtins.h"

#include "libft.h"

#include <stdlib.h>
#include <fcntl.h>

void					next_pipe(t_exec *exec, int *pipefd)
{
	unsigned char	i;

	if (exec->id)
	{
		i = 0;
		while (i != exec->id)
			close(pipefd[i++ * 2 + 1]);
		dup2(pipefd[(exec->id - 1) * 2], 0);
	}
	if (exec->args[exec->id + 1])
	{
		close(pipefd[exec->id * 2]);
		dup2(pipefd[exec->id * 2 + 1], 1);
	}
	launch_cmd(exec);
}

static unsigned int		get_process_index(pid_t *pids, pid_t pid)
{
	unsigned int	i;

	i = 0;
	while (pids[i] != pid)
		++i;
	return (i);
}

static void				treat_waits(t_exec_process *ep, t_exec *exec)
{
	t_pipecrash		**pipecrashes;
	int				status;
	pid_t			pid;
	unsigned int	i;

	pipecrashes = (t_pipecrash**)0;
	while ((pid = wait(&status)) > -1)
	{
		if (exec->args[(i = get_process_index(ep->ids, pid)) + 1])
			close(ep->pipes[2 * i + 1]);
		if (i)
			close(ep->pipes[2 * (i - 1)]);
		if (WIFEXITED(status))
			g_sh.last_ret = WEXITSTATUS(status);
		else
			pipes_crash_push(&pipecrashes, *exec->args[i],
				(g_sh.last_ret = 128 + WTERMSIG(status)));
	}
	if (pipecrashes)
		pipes_crash_print(pipecrashes);
}

void					exec_pipes(t_exec *exec)
{
	t_exec_process	ep;
	pid_t			fork_ret;

	exec_pipes_init(exec, &ep);
	while (exec->args[exec->id])
	{
		if (exec->args[exec->id + 1])
			pipe(ep.pipes + exec->id * 2);
		if (!(fork_ret = fork()))
			next_pipe(exec, ep.pipes);
		else if (fork_ret != -1)
		{
			ep.names[exec->id] = *exec->args[exec->id];
			ep.ids[exec->id] = fork_ret;
		}
		else
			error("fork failed", (char*)0);
		++exec->id;
	}
	treat_waits(&ep, exec);
	free(ep.names);
	free(ep.ids);
	free(ep.pipes);
}
