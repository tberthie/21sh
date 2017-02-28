/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfontani <tfontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 17:10:43 by tfontani          #+#    #+#             */
/*   Updated: 2017/02/19 16:09:45 by tfontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "sh.h"

#include "libft.h"

#include <stdlib.h>

static void		print_alias(void)
{
	unsigned int	i;

	i = 0;
	while (g_sh.alias_k[i])
	{
		ft_putstr(g_sh.alias_k[i]);
		ft_putchar('=');
		ft_putstr(g_sh.alias_v[i]);
		ft_putchar('\n');
		++i;
	}
}

unsigned char	alias(char **arg)
{
	char	*ptr;
	int		i;

	if (!*arg)
		print_alias();
	else
		while (*arg)
		{
			if ((ptr = ft_strchr(*arg, '=')))
			{
				*ptr = '\0';
				if ((i = ft_strarrstr(g_sh.alias_k, *arg)) != -1)
				{
					free(g_sh.alias_v[i]);
					g_sh.alias_v[i] = ft_strdup(ptr + 1);
				}
				else
				{
					ft_parrpush((void***)&g_sh.alias_k, ft_strdup(*arg));
					ft_parrpush((void***)&g_sh.alias_v, ft_strdup(ptr + 1));
				}
			}
			++arg;
		}
	return (0);
}
