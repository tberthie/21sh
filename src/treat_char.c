/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 19:57:58 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/20 19:57:59 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "sh.h"
#include "func.h"
#include "completion.h"

#include <unistd.h>

static void		treat_esc(void)
{
	char	c;

	if (read(0, &c, 1) == 1)
	{
		if (c == '[' && read(0, &c, 1) == 1)
		{
			if (c == 'A' || c == 'B')
				navigate_history((c == 'A') ? -1 : 1);
			else if (c == 'C' || c == 'D')
				func_cursor((c == 'C') ? 1 : -1);
			else if (c == '3' && read(0, &c, 1) == 1 && c == '~'
			&& g_sh.line[g_sh.l])
				func_delete(0);
			else if (c == '1' && read(0, &c, 1) == 1 && c == ';'
			&& read(0, &c, 1) == 1 && c == '2' && read(0, &c, 1) == 1)
				(c == 'C') ? func_mv_cu_af() : func_mv_cu_be();
		}
	}
}

void			treat_char(char c)
{
	if (c == '\t')
		completion();
	else if (c == 27)
		treat_esc();
	else if (c == 127)
		func_delete(1);
	else
		func_shortcut(c);
}
