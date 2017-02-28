/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfontani <tfontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 16:00:09 by tfontani          #+#    #+#             */
/*   Updated: 2017/02/20 19:54:32 by tfontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "func.h"
#include "sh.h"
#include "termcap.h"
#include "input.h"
#include "math.h"

#include "libft.h"

#include <stdlib.h>
#include <unistd.h>

void	func_clear(void)
{
	perform_termcap("cl");
	print_prompt();
	write_term(g_sh.line, g_sh.prompt.len);
	move_cursor(g_sh.prompt.len + (unsigned short)ft_strlen(g_sh.line),
		g_sh.l - (short)ft_strlen(g_sh.line));
}

void	func_delete(unsigned char back)
{
	if ((back && g_sh.l) || (!back && g_sh.line[g_sh.l]))
	{
		if (back)
		{
			move_cursor(g_sh.l + g_sh.prompt.len, -1);
			--g_sh.l;
		}
		ft_strrem(g_sh.line + g_sh.l);
		ft_strpush(&g_sh.line, ' ');
		write_term(g_sh.line + g_sh.l, g_sh.l + g_sh.prompt.len);
		ft_strrem(g_sh.line + ft_strlen(g_sh.line) - 1);
		move_cursor((unsigned short)ft_strlen(g_sh.line) + g_sh.prompt.len + 1,
			g_sh.l - (short)ft_strlen(g_sh.line) - 1);
	}
}

void	func_cursor(signed char shift)
{
	if ((shift == -1 && g_sh.l) || (shift == 1 && g_sh.line[g_sh.l]))
	{
		move_cursor(g_sh.l + g_sh.prompt.len, (short)shift);
		g_sh.l += shift;
	}
}

void	func_shortcut(char c)
{
	if (c == -61 && read(0, &c, 1) == 1 && c == -89)
		func_copy();
	else if (c == -30 && read(0, &c, 1) == 1
	&& c == -120 && read(0, &c, 1) == 1 && c == -102)
		func_paste();
	else if (c == 2)
		func_mv_wo(-1);
	else if (c == 4)
		func_ctrl_d();
	else if (c == 6)
		func_mv_wo(1);
	else if (c == 12)
		func_clear();
	else if (c == 18)
		research_history();
	else if (c == 21)
		func_cl_bf_cu();
}
