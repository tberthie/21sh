/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_ls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 16:28:24 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/28 16:28:26 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"
#include "sh.h"
#include "input.h"
#include "def.h"

#include "libft.h"

#define C 0
#define R 1
#define X 2
#define Y 3
#define LEN 4
#define I 5
#define ARRLEN 6

static void		ls(char **match)
{
	unsigned int	u[7];

	u[LEN] = ft_strarrstrlen(match) + NB_SPACES_LS;
	if (!(u[C] = g_sh.term_cols / u[LEN]))
		u[C] = 1;
	u[ARRLEN] = ft_parrlen((void**)match);
	u[R] = u[ARRLEN] / u[C] + (u[ARRLEN] % u[C] != 0);
	u[Y] = 0;
	while (u[Y] != u[R])
	{
		u[X] = 0;
		while (u[X] != u[C])
		{
			if ((u[I] = u[X] * u[R] + u[Y]) < u[ARRLEN])
			{
				ft_putstr(match[u[I]]);
				if (u[X] + 1 != u[C])
					ft_putnchar(' ', u[LEN] - ft_strlen(match[u[I]]));
			}
			++u[X];
		}
		ft_putchar('\n');
		++u[Y];
	}
}

void			completion_ls(char **match)
{
	validate_line();
	ls(match);
	print_prompt();
	write_term(g_sh.line, g_sh.prompt.len);
	move_cursor(g_sh.prompt.len + (unsigned short)ft_strlen(g_sh.line),
		g_sh.l - (short)ft_strlen(g_sh.line));
}
