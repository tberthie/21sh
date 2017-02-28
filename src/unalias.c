/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unalias.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfontani <tfontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 17:24:51 by tfontani          #+#    #+#             */
/*   Updated: 2017/02/01 17:40:10 by tfontani         ###   ########.fr       */
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
