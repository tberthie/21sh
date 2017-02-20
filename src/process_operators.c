/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_operators.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 16:18:18 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/20 19:57:22 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process_operators.h"

#include "operator.h"
#include "sh.h"
#include "split_args.h"
#include "libft.h"

#include <stdlib.h>

static void		preprocess(t_exec *cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	while (cmd->args[i])
	{
		tmp = ft_strdup(*(cmd->args[i]));
		ft_parrfree((void**)cmd->args[i]);
		cmd->args[i++] = split_args(tmp);
		free(tmp);
	}
	exec(cmd);
	cmd->id = CMD;
}

static void		skip(t_exec **execs)
{
	while (*execs && (*execs)->id != SEP)
		execs++;
	if (*execs)
		process_operators(execs + 1);
}

void			process_operators(t_exec **execs)
{
	preprocess(*execs++);
	if (*execs && (*execs)->id == AND)
	{
		if (!g_sh.last_ret)
			process_operators(execs + 1);
		else if (*(execs + 2) && (*(execs + 2))->id == OR)
			process_operators(execs + 3);
		else
			skip(execs);
		return ;
	}
	else if (*execs && (*execs)->id == OR)
	{
		if (g_sh.last_ret)
			process_operators(execs + 1);
		else if (*(execs + 2) && (*(execs + 2))->id == AND)
			process_operators(execs + 3);
		else
			skip(execs);
		return ;
	}
	skip(execs);
}
