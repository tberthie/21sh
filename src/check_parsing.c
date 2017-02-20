/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 20:55:29 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/20 19:55:10 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_parsing.h"

#include "libft.h"
#include "operator.h"
#include "parse.h"
#include "input.h"
#include "error.h"
#include "sh.h"

#include <stdlib.h>

static char		process_status(unsigned char status, char *line, t_exec **execs)
{
	char	*tmp;

	if (status && !g_sh.is_sourcing)
		input_again(operator_name(status));
	else if (status)
	{
		error((tmp = ft_strsjoin("parsing error near '", "'",
		operator_str((*(execs - 1))->id))), 0);
		free(tmp);
		free(line);
	}
	return (status) ? 0 : 1;
}

char			check_parsing(t_exec **execs, char *line)
{
	unsigned char	status;
	char			*tmp;

	if (!*execs)
		return (1);
	status = 1;
	while (*execs)
	{
		if ((*execs)->id == CMD)
			status = 0;
		else if (!status)
			status = (*execs)->id;
		else
		{
			error((tmp = ft_strsjoin("parsing error near '", "'",
			operator_str((*execs)->id))), 0);
			free(tmp);
			free(line);
			return (0);
		}
		execs++;
	}
	return (process_status(status, line, execs));
}
