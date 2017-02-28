/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 16:29:01 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/28 16:29:02 by tberthie         ###   ########.fr       */
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

void			parse_error(unsigned char op)
{
	char	*op_str;

	write(2, "\x1b[31m"SH_NAME"\x1b[0m: parse error near '", ft_strlen(SH_NAME)
		+ 30);
	op_str = operator_str(op);
	write(2, op_str, ft_strlen(op_str));
	write(2, "'\n", 2);
}

static char		*get_signal_str_bis(unsigned char sig)
{
	if (sig == 141)
		return ("broken pipe");
	if (sig == 142)
		return ("alarm clock");
	return ("terminated");
}

static char		*get_signal_str(unsigned char sig)
{
	if (sig == 129)
		return ("hang up instruction");
	if (sig == 131)
		return ("quit");
	if (sig == 132)
		return ("illegal instruction");
	if (sig == 133)
		return ("trace/breakpoint trap");
	if (sig == 134)
		return ("abort");
	if (sig == 135)
		return ("emulation trap");
	if (sig == 136)
		return ("arithmetic exception");
	if (sig == 137)
		return ("kill instruction");
	if (sig == 138)
		return ("bus error");
	if (sig == 139)
		return ("segmentation fault");
	if (sig == 140)
		return ("bad system call");
	return (get_signal_str_bis(sig));
}

void			print_exit_signal(unsigned char sig, char *bin)
{
	char	*str;

	if (sig == 130)
		ft_putchar('\n');
	else if (sig > 128 && sig < 144)
	{
		str = get_signal_str(sig);
		error(str, bin);
	}
	else
	{
		str = ft_itoa((int)sig);
		error("process exited with signal", str);
		free(str);
	}
}
