/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfontani <tfontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 19:54:53 by tfontani          #+#    #+#             */
/*   Updated: 2017/02/28 15:59:05 by tberthie         ###   ########.fr       */
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
	int		i;

	i = 0;
	*line += new;
	while (**line == ' ' || **line == '\t')
		(*line)++;
	while ((*pipe)[i] == ' ' || *(pipe[i]) == '\t')
		i++;
	if (!ft_strlen(&(*pipe)[i]))
	{
		free(*pipe);
		return (!new && !**line) ? INPUT : ERROR;
	}
	ft_parrpush((void***)pipes, *pipe);
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

	if ((status = split_pipes(line, &pipes)) == INPUT && !g_sh.is_sourcing &&
	*pipes)
		input_again("pipe");
	else if ((status == ERROR || (status == INPUT && (g_sh.is_sourcing ||
	!*pipes))))
	{
		status = ERROR;
		error(*pipes ? "parsing error near '|'" : "invalid command syntax", 0);
	}
	else if (*pipes && !status)
	{
		exec = (t_exec*)ft_m(sizeof(t_exec));
		exec->id = CMD;
		exec->args = (char***)ft_parrnew();
		exec->redirs = (t_redirection***)ft_parrnew();
		ft_parrpush((void***)execs, exec);
		status = split_pipeline(pipes, exec);
	}
	ft_parrfree((void**)pipes);
	return (status);
}
