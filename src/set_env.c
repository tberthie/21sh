/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 19:57:37 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/20 19:57:38 by tberthie         ###   ########.fr       */
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
	if ((i = ft_strarrstrn(g_sh.env, var, ft_strlen(var))) != -1)
	{
		free(g_sh.env[i]);
		ft_parrrem((void**)g_sh.env + i);
	}
	*v = c;
}

void			set_env(char *arg)
{
	char	*ptr;

	if ((ptr = ft_strchr(arg, '=')))
	{
		check_existing(arg, ptr + 1);
		ft_parrpush((void***)&g_sh.env, ft_strdup(arg));
		env_check(arg);
	}
}

unsigned char	builtin_setenv(char **args)
{
	while (*args)
		set_env(*args++);
	return (0);
}
