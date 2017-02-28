/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 17:18:58 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/28 17:18:59 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_redirs.h"

#include "libft.h"
#include "operator.h"
#include "parse_exec.h"
#include "input.h"
#include "error.h"

#include <fcntl.h>

static t_redirection	*create_redir(unsigned char type, int fd, char *s)
{
	t_redirection	*redir;

	redir = (t_redirection*)ft_m(sizeof(t_redirection));
	redir->type = type;
	redir->fd_src = fd;
	redir->s = s;
	return (redir);
}

static char				*get_redir_word(char **pipe, char *status)
{
	char		*word;
	char		quote;

	quote = 0;
	word = ft_strnew();
	while (**pipe == ' ' || **pipe == '\t')
		(*pipe)++;
	while (**pipe && ((operator_id(*pipe) == CMD && **pipe != ' '
	&& **pipe != '\t') || quote))
	{
		if (**pipe == quote)
			quote -= *(*pipe)++;
		else if ((**pipe == '\'' || **pipe == '"') && !quote)
			quote = *(*pipe)++;
		else if (**pipe == '\\' && (*pipe += 1))
			ft_strpush(&word, *(*pipe)++);
		else
			ft_strpush(&word, *(*pipe)++);
	}
	if (!ft_strlen(word))
		*status = ERROR;
	return (word);
}

static char				check_fd(char *word)
{
	char		status;

	status = 0;
	if (*word == '-' && !*(word + 1))
		return (0);
	else
		while (!status && *word)
		{
			if (*word < '0' || *word > '9')
				status = INPUT;
			word++;
		}
	if (status)
		error("bad file descriptor", 0);
	return (status);
}

static char				get_redir(char **pipe, t_redirection ***redirs)
{
	char			status;
	unsigned char	id;
	t_redirection	*redir;

	status = 0;
	id = redir_id(*pipe);
	redir = create_redir(id, id == OUT || id == APP
	|| id == DUP_OUT ? 1 : 0, 0);
	if (**pipe >= '0' && **pipe <= '9')
		redir->fd_src = *(*pipe)++ - '0';
	*pipe += (id > NONE) + (id > OUT);
	redir->s = get_redir_word(pipe, &status);
	if (!status && id == HERE)
		redir->s = heredoc(redir->s);
	else if (!status && (id == DUP_IN || id == DUP_OUT))
		status = check_fd(redir->s);
	ft_parrpush((void***)redirs, redir);
	if (status == ERROR)
		error("bad redirection syntax", 0);
	return (status);
}

char					parse_redirs(char *pipe, t_exec *exec)
{
	t_redirection	**redirs;
	char			status;
	char			quote;
	char			*beg;

	quote = 0;
	status = 0;
	redirs = (t_redirection**)ft_parrnew();
	while (!status && *pipe)
		if ((*pipe == '\'' || *pipe == '"') && !quote)
			quote = *pipe++;
		else if (quote == *pipe)
			quote -= *pipe++;
		else if (quote || !redir_id(pipe))
			pipe++;
		else if ((beg = pipe) &&
		!(status = get_redir(&pipe, &redirs)))
		{
			ft_strcpy(beg, pipe);
			pipe = beg;
		}
	if (!status && !*redirs)
		ft_parrpush((void***)&redirs, create_redir(NONE, 0, 0));
	ft_parrpush((void***)&exec->redirs, redirs);
	return (status);
}
