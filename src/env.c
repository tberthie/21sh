/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 16:28:43 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/28 16:28:45 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "builtins.h"
#include "parse.h"

#include "libft.h"

#include <stdlib.h>

static void		print_env(void)
{
	char	**env;

	env = g_sh.env;
	while (*env)
	{
		ft_putstr(*env++);
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

static void		remove_env_var(char **env, char *var)
{
	int		i;

	if ((i = ft_strarrstrn(env, var, ft_strlen(var))) != -1)
	{
		free(env[i]);
		ft_parrrem((void**)env + i);
	}
}

static void		parse_env(char **args)
{
	char	**env;
	char	*line;

	line = 0;
	env = ft_strarrdup(g_sh.env);
	while (!line && *args)
	{
		if ((*args)[0] != '-')
			line = fill_line(args);
		else if ((*args)[1] == 'i')
		{
			ft_parrfree((void**)env);
			env = (char**)ft_parrnew();
		}
		else if ((*args)[1] == 'u' && args[1])
			remove_env_var(env, *++args);
		++args;
	}
	ft_ptrswap((void**)&env, (void**)&g_sh.env);
	if (line)
		exec_cmd(line);
	else
		print_env();
	ft_ptrswap((void**)&env, (void**)&g_sh.env);
	ft_parrfree((void**)env);
}

unsigned char	env(char **args)
{
	if (!*args)
		print_env();
	else
		parse_env(args);
	return (0);
}
