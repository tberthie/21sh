/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 17:21:52 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/20 19:57:12 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operator.h"

#include "libft.h"
#include "parse_exec.h"

char			*operator_str(unsigned char op)
{
	if (op == OR)
		return ("||");
	if (op == AND)
		return ("&&");
	if (op == SEP)
		return (";");
	return ("");
}

char			*operator_name(unsigned char op)
{
	if (op == OR)
		return ("or");
	if (op == AND)
		return ("and");
	if (op == SEP)
		return ("sep");
	return ("");
}

unsigned char	operator_id(char *cmd)
{
	if (*cmd == ';' || *cmd == '\n')
		return (SEP);
	else if (*cmd == '|' && *(cmd + 1) == '|')
		return (OR);
	else if (*cmd == '&' && *(cmd + 1) == '&')
		return (AND);
	return (CMD);
}

unsigned char	redir_id(char *line)
{
	if (*line >= '0' && *line <= '9')
		line++;
	if (*line == '>' && *(line + 1) == '>')
		return (APP);
	if (*line == '>' && *(line + 1) == '&')
		return (DUP_OUT);
	if (*line == '>')
		return (OUT);
	if (*line == '<' && *(line + 1) == '<')
		return (HERE);
	if (*line == '<' && *(line + 1) == '&')
		return (DUP_IN);
	if (*line == '<')
		return (IN);
	return (NONE);
}
