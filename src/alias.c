/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 19:54:59 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/20 19:55:00 by tberthie         ###   ########.fr       */
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
