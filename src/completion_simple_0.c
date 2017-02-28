/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_simple_0.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfontani <tfontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 14:57:19 by tfontani          #+#    #+#             */
/*   Updated: 2017/02/07 19:07:49 by tfontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"
#include "sh.h"
#include "input.h"

#include "libft.h"

#include <stdlib.h>

static void		completion_simple(t_completion *c)
{
	unsigned int	matching_len;
	unsigned int	i;

	matching_len = ft_strlen(c->str);
	i = 0;
	while (c->dc[i])
	{
		if (!matching_len || !ft_strncmp(c->str, c->dc[i], matching_len))
			ft_parrpush((void***)&c->match, c->dc[i]);
		++i;
	}
}

void			completion_simple_file(t_completion *c)
{
	completion_simple(c);
	if (*c->match)
		completion_simple_complete(c);
	else
		ft_putchar('\a');
}

void			completion_simple_command(t_completion *c)
{
	char	**path;
	char	**dc;

	path = g_sh.path;
	ft_parrfree((void**)c->dc);
	c->dc = (char**)ft_parrnew();
	while (*path)
		if ((dc = ft_gdc(*path++)))
		{
			ft_freeswap((void**)&c->dc, ft_parrjoin((void**)c->dc, (void**)dc));
			free(dc);
		}
	completion_simple(c);
	if (*c->match)
		completion_simple_complete(c);
}
