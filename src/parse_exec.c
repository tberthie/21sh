/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfontani <tfontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 19:54:51 by tfontani          #+#    #+#             */
/*   Updated: 2017/02/28 15:24:24 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_exec.h"

#include "parse_pipeline.h"
#include "execution.h"
#include "operator.h"
#include "libft.h"
#include "input.h"
#include "parse.h"
#include "error.h"
#include "sh.h"

#include <stdlib.h>

static char			parse_operator(t_exec ***execs, char **line)
{
	t_exec		*op;

	op = (t_exec*)ft_m(sizeof(t_exec));
	op->id = operator_id(*line);
	*line += (op->id > CMD) + (op->id > SEP);
	ft_parrpush((void***)execs, op);
	return (0);
}

static char			get_exec(t_exec ***execs, char **line)
{
	char	status;

	status = (operator_id(*line) == CMD) ? parse_pipeline(execs, line) :
	parse_operator(execs, line);
	if (!g_sh.is_sourcing && (status == '\'' || status == '"'))
		input_again(status == '\'' ? "quote" : "dquote");
	else if (status == '\'' || status == '"')
	{
		error(status == '\'' ? "parsing error near ''" :
		"parsing error near \"\"", 0);
		status = ERROR;
	}
	return (status);
}

t_exec				**parse_exec(char *line)
{
	t_exec		**execs;
	char		status;
	char		*beg;

	beg = line;
	execs = (t_exec**)ft_parrnew();
	while (*line)
	{
		while (*line == ' ' || *line == '\t')
			line++;
		if (*line == '#')
			while (*line && *line != '\n')
				line++;
		if (*line && (status = get_exec(&execs, &line)))
		{
			if (status == ERROR)
				free(beg);
			free_execs(execs);
			return (0);
		}
	}
	return (execs);
}
