/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 13:50:27 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/20 19:57:14 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

#include "libft.h"
#include "error.h"
#include "sh.h"
#include "input.h"
#include "operator.h"
#include "parse_exec.h"
#include "check_parsing.h"
#include "process_operators.h"

#include <stdlib.h>

static void		free_redirs(t_redirection ***redirs)
{
	t_redirection	***beg;
	int				pos;

	beg = redirs;
	while (*redirs)
	{
		pos = 0;
		while ((*redirs)[pos])
		{
			if (((*redirs)[pos])->s)
				free(((*redirs)[pos])->s);
			pos++;
		}
		ft_parrfree((void**)*redirs++);
	}
	free(beg);
}

void			free_execs(t_exec **execs)
{
	t_exec		**beg;
	char		***args_beg;

	beg = execs;
	while (*execs)
	{
		if ((*execs)->id == CMD)
		{
			args_beg = (*execs)->args;
			while (*(*execs)->args)
				ft_parrfree((void**)*(*execs)->args++);
			free(args_beg);
			free_redirs((*execs)->redirs);
		}
		execs++;
	}
	ft_parrfree((void**)beg);
}

void			exec_cmd(char *line)
{
	t_exec		**execs;

	if ((execs = parse_exec(line)))
	{
		if (check_parsing(execs, line))
		{
			free(line);
			if (*execs)
				process_operators(execs);
		}
		free_execs(execs);
	}
}
