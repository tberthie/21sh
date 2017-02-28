/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unalias.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 17:19:38 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/28 17:19:39 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "sh.h"
#include "error.h"

#include "libft.h"

#include <stdlib.h>

unsigned char	unalias(char **arg)
{
	int		i;

	while (*arg)
	{
		if ((i = ft_strarrstr(g_sh.alias_k, *arg)) != -1)
		{
			ft_strarrrem(g_sh.alias_k + i);
			ft_strarrrem(g_sh.alias_v + i);
		}
		else
			error("unalias: no such alias", *arg);
		++arg;
	}
	return (0);
}
