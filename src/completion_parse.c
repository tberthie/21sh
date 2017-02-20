/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_parse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 19:55:19 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/20 19:55:20 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"
#include "sh.h"

#include "libft.h"

#include <stdlib.h>

static void		retrieve_str_to_complete(t_completion *c)
{
	unsigned int	i;

	i = g_sh.l;
	while (i && g_sh.line[--i] != ' ')
		;
	i += (i != 0);
	c->beg = (unsigned short)i;
	c->str = ft_strnew();
	while (g_sh.line[i] && g_sh.line[i] != ' ')
	{
		if (g_sh.line[i] == '\\')
			ft_strpush(&c->str, g_sh.line[++i]);
		else if (g_sh.line[i] != '~')
			ft_strpush(&c->str, g_sh.line[i]);
		else
			ft_strspush(&c->str, g_sh.home);
		++i;
	}
	c->end = (unsigned short)i;
}

static void		retrieve_dc_to_complete(t_completion *c)
{
	char	*ptr;

	if ((ptr = ft_strrchr(c->str, '/')))
	{
		*ptr = '\0';
		c->dir = ft_strdup((ptr == c->str) ? "/" : c->str);
		ptr = ft_strdup(ptr + 1);
		free(c->str);
		c->str = ptr;
		c->type = CT_SIMPLE_FILE;
	}
	else
	{
		c->dir = ft_strdup(".");
		c->type = (c->beg != 0) ? CT_SIMPLE_FILE : CT_SIMPLE_COMMAND;
	}
	c->dc = ft_gdc(c->dir);
}

void			retrieve_completion_info(t_completion *c)
{
	retrieve_str_to_complete(c);
	retrieve_dc_to_complete(c);
}
