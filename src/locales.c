/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locales.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 17:18:40 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/28 17:18:42 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "builtins.h"
#include "parse.h"

#include "libft.h"

#include <stdlib.h>

static void		print_locals(void)
{
	char	**locals;

	locals = g_sh.locales;
	while (*locals)
	{
		ft_putstr(*locals++);
		ft_putchar('\n');
	}
}

static char		*fill_line(char **args)
{
	char	*line;

	line = ft_strnew();
	while (*args)
		ft_freeswap((void**)&line, ft_strcjoin(line, *args++, ' '));
	return (line);
}

static void		remove_locals_var(char **locals, char *var)
{
	int		i;

	if ((i = ft_strarrstrn(locals, var, ft_strlen(var))) != -1)
	{
		free(locals[i]);
		ft_parrrem((void**)locals + i);
	}
}

static void		parse_locals(char **args)
{
	char	**locals;
	char	*line;

	line = 0;
	locals = ft_strarrdup(g_sh.locales);
	while (!line && *args)
	{
		if ((*args)[0] != '-')
			line = fill_line(args);
		else if ((*args)[1] == 'i')
		{
			ft_parrfree((void**)locals);
			locals = (char**)ft_parrnew();
		}
		else if ((*args)[1] == 'u' && args[1])
			remove_locals_var(locals, *++args);
		++args;
	}
	ft_ptrswap((void**)&locals, (void**)&g_sh.locales);
	if (line)
		exec_cmd(line);
	else
		print_locals();
	ft_ptrswap((void**)&locals, (void**)&g_sh.locales);
	ft_parrfree((void**)locals);
}

unsigned char	locals(char **args)
{
	if (!*args)
		print_locals();
	else
		parse_locals(args);
	return (0);
}
