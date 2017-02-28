/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_simple_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 16:28:39 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/28 16:28:40 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"
#include "sh.h"
#include "input.h"

#include "libft.h"

#include <stdlib.h>

static void		check_dir(t_completion *c)
{
	char	*result;

	result = ft_strcjoin(c->dir, *c->match, '/');
	ft_strins(&g_sh.line, (ft_isdir(result)) ? '/' : ' ',
		c->end + ft_strlen(*c->match) - ft_strlen(c->str));
	free(result);
}

static void		completion_simple_complete_multiple(t_completion *c)
{
	char			**match;
	unsigned int	matching_min;
	unsigned int	matching;

	matching_min = (unsigned int)-1;
	match = c->match;
	while (*++match)
	{
		matching = ft_stricmp(*match, match[-1]);
		if (matching < matching_min)
			matching_min = matching;
	}
	if (matching_min > ft_strlen(c->str))
	{
		match[-1][matching_min] = '\0';
		ft_strsins(&g_sh.line, match[-1] + ft_strlen(c->str), c->end);
		write_term(g_sh.line + g_sh.l, g_sh.prompt.len
			+ (unsigned short)ft_strlen(g_sh.line) - g_sh.l);
		g_sh.l += ft_strlen(match[-1]) - ft_strlen(c->str);
		move_cursor((unsigned short)ft_strlen(g_sh.line) + g_sh.prompt.len,
			g_sh.l - (short)ft_strlen(g_sh.line));
	}
	else
		completion_ls(c->match);
}

void			completion_simple_complete(t_completion *c)
{
	if (!c->match[1])
	{
		ft_strsins(&g_sh.line, *c->match + ft_strlen(c->str), c->end);
		check_dir(c);
		write_term(g_sh.line + g_sh.l, g_sh.prompt.len
			+ (unsigned short)ft_strlen(g_sh.line) - g_sh.l);
		g_sh.l += ft_strlen(*c->match) - ft_strlen(c->str) + 1;
		move_cursor((unsigned short)ft_strlen(g_sh.line) + g_sh.prompt.len,
			g_sh.l - (short)ft_strlen(g_sh.line));
	}
	else
		completion_simple_complete_multiple(c);
}
