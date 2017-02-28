/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfontani <tfontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 17:49:43 by tfontani          #+#    #+#             */
/*   Updated: 2017/02/24 14:50:48 by tfontani         ###   ########.fr       */
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
		if ((i = ft_strarrstrn(g_sh.env, *args, varlen)) != -1)
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
