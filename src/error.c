/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 11:54:09 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/20 19:55:48 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"
#include "error.h"
#include "libft.h"
#include "parse.h"
#include "operator.h"

#include "libft.h"

#include <stdlib.h>
#include <unistd.h>

void			error(char *msg, char *name)
{
	write(2, "\x1b[31m"SH_NAME"\x1b[0m: ", ft_strlen(SH_NAME) + 12);
	write(2, msg, ft_strlen(msg));
	if (name)
	{
		write(2, ": ", 2);
		write(2, name, ft_strlen(name));
	}
	write(2, "\n", 1);
}

void			parse_error(char op)
{
	write(2, "\x1b[31m"SH_NAME"\x1b[0m: parse error near '", ft_strlen(SH_NAME)
		+ 30);
	op == SEP ? write(2, ";", 1) : 0;
	op == AND ? write(2, "&&", 2) : 0;
	op == OR ? write(2, "||", 2) : 0;
	write(2, "'\n", 2);
}

static char		*get_signal_str(unsigned char sig)
{
	if (sig == 129)
		return ("HANG UP instruction");
	if (sig == 131)
		return ("QUIT instruction");
	if (sig == 132)
		return ("illegal instruction");
	if (sig == 133)
		return ("trace trap");
	if (sig == 134)
		return ("ABORT instruction");
	if (sig == 135)
		return ("bus error");
	if (sig == 136)
		return ("floating point exception");
	if (sig == 137)
		return ("KILL instruction");
	if (sig == 138)
		return ("user signal 1");
	if (sig == 139)
		return ("segmentation fault");
	if (sig == 140)
		return ("user signal 2");
	return ("broken pipe");
}

void			print_exit_signal(unsigned char sig, char *bin)
{
	char	*str;

	if (sig == 130)
		write(2, "^C\n", 3);
	else if (sig > 128 && sig < 142)
	{
		str = get_signal_str(sig);
		error(str, bin);
	}
	else
	{
		str = ft_itoa((int)sig);
		error("process killed", str);
		free(str);
	}
}
