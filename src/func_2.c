/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 17:18:18 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/28 17:18:19 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "func.h"
#include "sh.h"
#include "input.h"
#include "config.h"

#include <libft.h>

#include <stdlib.h>
#include <unistd.h>

void	func_mv_wo(signed short shift)
{
	unsigned short	c;

	c = g_sh.l;
	if ((shift == -1 && c) || (shift == 1 && g_sh.line[c]))
	{
		c += shift;
		while (c && g_sh.line[c] == ' ')
			c += shift;
		while (c && g_sh.line[c] && g_sh.line[c + shift] != ' ')
			c += shift;
		if (shift == 1 && g_sh.line[c])
		{
			++c;
			while (g_sh.line[c] == ' ')
				++c;
		}
		move_cursor(g_sh.l + g_sh.prompt.len, c - (short)g_sh.l);
		g_sh.l = c;
	}
}

void	func_ctrl_d(void)
{
	if (g_sh.l || *g_sh.line)
		func_delete(0);
	else
	{
		ft_putchar('\n');
		exit(quit());
	}
}
