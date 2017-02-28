/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_locales.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfontani <tfontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 14:03:39 by tfontani          #+#    #+#             */
/*   Updated: 2017/02/28 14:03:40 by tfontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "sh.h"
#include "env.h"
#include "error.h"

#include "libft.h"

#include <stdlib.h>

static void		check_existing(char *var, char *v)
{
	int		i;
	char	c;

	c = *v;
	*v = '\0';
	if ((i = ft_strarrstrn(g_sh.locales, var, ft_strlen(var))) != -1)
	{
		free(g_sh.locales[i]);
		ft_parrrem((void**)g_sh.locales + i);
	}
	*v = c;
}

void			set_local(char *arg)
{
	char	*ptr;

	if ((ptr = ft_strchr(arg, '=')))
	{
		check_existing(arg, ptr + 1);
		ft_parrpush((void***)&g_sh.locales, ft_strdup(arg));
	}
}

unsigned char	builtin_export(char **args)
{
	while (*args)
		set_local(*args++);
	return (0);
}

unsigned char	unset(char **args)
{
	unsigned int	varlen;
	int				i;
	char			*str;

	while (*args)
	{
		varlen = ft_strlen(*args);
		(*args)[varlen++] = '=';
		if ((i = ft_strarrstrn(g_sh.locales, *args, varlen)) != -1)
		{
			str = g_sh.locales[i];
			ft_parrrem((void**)g_sh.locales + i);
			free(str);
		}
		++args;
	}
	return (0);
}

char			*get_local(const char *name)
{
	char			**local;
	unsigned int	strlen;

	local = g_sh.locales;
	strlen = ft_strlen(name);
	while (*local && (ft_strncmp(name, *local, strlen) ||
	(*local)[strlen] != '='))
		++local;
	return (*local) ? *local + strlen + 1 : (char*)0;
}
