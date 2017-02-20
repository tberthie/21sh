/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 19:58:06 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/20 19:58:10 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "env.h"
#include "sh.h"

#include "libft.h"

#include <stdlib.h>

unsigned char	unset_env(char **args)
{
	unsigned int	varlen;
	int				i;
	char			*str;

	while (*args)
	{
		varlen = ft_strlen(*args);
		(*args)[varlen++] = '=';
		if ((i = ft_strarrstrn(g_sh.env, *args, varlen)))
		{
			str = g_sh.env[i];
			ft_parrrem((void**)g_sh.env + i);
			env_check(str);
			free(str);
		}
		++args;
	}
	return (0);
}
