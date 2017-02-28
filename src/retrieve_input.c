/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retrieve_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 17:19:12 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/28 17:19:13 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "sh.h"
#include "parse.h"
#include "termcap.h"
#include "config.h"

#include "libft.h"

#include <stdlib.h>
#include <unistd.h>

static void		print_char(char c)
{
	if (!g_sh.line[g_sh.l])
	{
		ft_strpush(&g_sh.line, c);
		write_term(g_sh.line + g_sh.l, g_sh.l + g_sh.prompt.len);
	}
	else
	{
		ft_strins(&g_sh.line, c, g_sh.l);
		write_term(g_sh.line + g_sh.l, g_sh.l + g_sh.prompt.len);
		move_cursor((unsigned short)ft_strlen(g_sh.line) + g_sh.prompt.len,
			(short)g_sh.l - (short)ft_strlen(g_sh.line) + 1);
	}
	++g_sh.l;
}

void			retrieve_input(void)
{
	char	c;

	g_sh.is_inputting = 1;
	g_sh.l = 0;
	if (g_sh.interrupted)
		g_sh.interrupted = 0;
	g_sh.line = ft_strnew();
	while (read(0, &c, 1) == 1 && c != '\n')
	{
		if (c > 31 && c < 127)
			print_char(c);
		else
			treat_char(c);
	}
	g_sh.is_inputting = 0;
	validate_line();
}
