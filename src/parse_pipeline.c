/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 15:05:16 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/20 19:57:16 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_pipeline.h"

#include "operator.h"
#include "parse_exec.h"
#include "split_pipeline.h"
#include "libft.h"
#include "replace_parameters.h"
#include "input.h"
#include "error.h"
#include "sh.h"

#include <stdlib.h>

static char		check_pipe(char **line, char **pipe, char ***pipes, char new)
{
	ft_parrpush((void***)pipes, *pipe);
	*line += new;
	while (**line == ' ' || **line == '\t')
		(*line)++;
	if (!ft_strlen(*pipe))
		return (!new && !**line) ? INPUT : ERROR;
	if (new)
		*pipe = ft_strnew();
	return (0);
}

static char		push_char(char **pipe, char **line, char quote)
{
	if (**line == quote)
		quote = 0;
	else if ((**line == '\'' || **line == '"') && !quote)
		quote = **line;
	else if (**line == '\\')
		ft_strpush(pipe, *(*line)++);
	ft_strpush(pipe, *(*line)++);
	return (quote);
}

static char		split_pipes(char **line, char ***pipes)
{
	char		*pipe;
	char		error;
	char		quote;

	quote = 0;
	error = 0;
	pipe = ft_strnew();
	*pipes = (char**)ft_parrnew();
	while (!error && **line && ((operator_id(*line) == CMD
	&& **line != '#') || quote))
	{
		if (**line == '|' && !quote)
			error = check_pipe(line, &pipe, pipes, 1);
		else if (**line == '$' && quote != '\'')
			replace_params(&pipe, line);
		else if (**line == '~' && !quote)
			replace_tilde(&pipe, line);
		else
			quote = push_char(&pipe, line, quote);
	}
	if (quote)
		free(pipe);
	if (!error && !quote)
		error = check_pipe(line, &pipe, pipes, 0);
	return (error) ? error : quote;
}

char			parse_pipeline(t_exec ***execs, char **line)
{
	t_exec			*exec;
	char			**pipes;
	char			status;

	exec = (t_exec*)ft_m(sizeof(t_exec));
	exec->id = CMD;
	exec->args = (char***)ft_parrnew();
	exec->redirs = (t_redirection***)ft_parrnew();
	ft_parrpush((void***)execs, exec);
	if ((status = split_pipes(line, &pipes)) == INPUT && !g_sh.is_sourcing)
		input_again("pipe");
	else if (status == ERROR || (status == INPUT && g_sh.is_sourcing))
	{
		status = ERROR;
		error("parsing error near '|'", 0);
	}
	else if (!status)
		status = split_pipeline(pipes, exec);
	ft_parrfree((void**)pipes);
	return (status);
}
