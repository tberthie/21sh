/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfontani <tfontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 14:36:27 by tfontani          #+#    #+#             */
/*   Updated: 2017/02/26 15:09:26 by tfontani         ###   ########.fr       */
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

void	move_cursor(unsigned short c, short shift)
{
	if (shift < 0)
	{
		if (c / g_sh.term_cols == (c + shift) / g_sh.term_cols)
			perform_termcap_nb(T_CM_LEFT, (unsigned short)ABS(shift));
		else
		{
			perform_termcap(T_CM_UP);
			perform_termcap_nb(T_CM_RIGHT, g_sh.term_cols - 1);
			move_cursor(c - c % g_sh.term_cols - 1,
				shift + c % g_sh.term_cols + 1);
		}
	}
	else if (shift > 0)
	{
		if (c / g_sh.term_cols == (c + shift) / g_sh.term_cols)
			perform_termcap_nb(T_CM_RIGHT, (unsigned short)shift);
		else
		{
			perform_termcap(T_CM_DOWN);
			move_cursor(c + g_sh.term_cols - c % g_sh.term_cols,
				shift - (g_sh.term_cols - c % g_sh.term_cols));
		}
	}
}

void	write_term(char *str, unsigned short c)
{
	unsigned int	strlen;

	strlen = ft_strlen(str);
	if (!(c % g_sh.term_cols) && c
	&& c / g_sh.term_cols == (c + strlen) / g_sh.term_cols)
	{
		perform_termcap(T_CM_UP);
		perform_termcap_nb(T_CM_RIGHT, g_sh.term_cols - 1);
		ft_putchar(str[-1]);
	}
	write(1, str, strlen);
	if (!((c + strlen) % g_sh.term_cols) && c)
		perform_termcap(T_CM_DOWN);
}

void	clear_line(void)
{
	char	*str;

	move_cursor(g_sh.l + g_sh.prompt.len, -(short)g_sh.l);
	str = ft_strfrmchr(' ', ft_strlen(g_sh.line));
	write_term(str, g_sh.prompt.len);
	free(str);
	move_cursor((unsigned short)ft_strlen(g_sh.line) + g_sh.prompt.len,
		-(short)ft_strlen(g_sh.line));
}

void	check_cursor_pos(void)
{
	unsigned int	pos;
	char			b[4];

	write(1, "\033[6n", 4);
	read(0, b, 4);
	if (b[3] != ';')
		while (read(0, b, 1) == 1 && *b != ';')
			;
	pos = 0;
	while (read(0, b, 1) == 1 && *b != 'R')
		pos = pos * 10 + (unsigned int)(*b - '0');
	if (pos != 1)
	{
		perform_termcap("so");
		perform_termcap("mr");
		ft_putchar('%');
		perform_termcap("se");
		ft_putchar('\n');
	}
}
