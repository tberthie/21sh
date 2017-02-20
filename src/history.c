/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 19:56:57 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/20 19:56:58 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "func.h"
#include "sh.h"
#include "input.h"
#include "def.h"
#include "config.h"
#include "error.h"

#include "libft.h"

#include <stdlib.h>

void			add_to_history(char *line)
{
	int		i;

	if (*line)
	{
		if ((i = ft_strarrstr(g_sh.history, line)) != -1)
		{
			free(g_sh.history[i]);
			ft_parrrem((void**)g_sh.history + i);
		}
		ft_parrpush((void***)&g_sh.history, ft_strdup(line));
	}
	g_sh.h = (unsigned short)ft_parrlen((void**)g_sh.history);
}

static void		move_cursor_up_down(signed char shift)
{
	short	cursor_shift;

	if (shift == -1)
		cursor_shift = (g_sh.l < g_sh.term_cols) ?
			-(short)g_sh.l : -(short)g_sh.term_cols;
	else
		cursor_shift = ((unsigned short)ft_strlen(g_sh.line) - g_sh.l
			< g_sh.term_cols) ?
			(short)ft_strlen(g_sh.line) - g_sh.l : (short)g_sh.term_cols;
	move_cursor(g_sh.prompt.len + g_sh.l, cursor_shift);
	g_sh.l += cursor_shift;
}

void			navigate_history(signed char shift)
{
	if ((shift == -1 && g_sh.l + g_sh.prompt.len >= g_sh.term_cols)
	|| (shift == 1 && (g_sh.l + g_sh.prompt.len) / g_sh.term_cols
	!= (g_sh.prompt.len + ft_strlen(g_sh.line)) / g_sh.term_cols))
		move_cursor_up_down(shift);
	else if ((shift == -1 && g_sh.h) || (shift == 1 && g_sh.history[g_sh.h]))
	{
		clear_line();
		free(g_sh.line);
		g_sh.h += shift;
		g_sh.line = ft_strnew();
		ft_strspush(&g_sh.line, (g_sh.history[g_sh.h]) ?
			g_sh.history[g_sh.h] : "");
		write_term(g_sh.line, g_sh.prompt.len);
		g_sh.l = (unsigned short)ft_strlen(g_sh.line);
	}
}

static void		reverse_search(void)
{
	char	*found;

	found = ft_strarrstrstrr(g_sh.history, g_sh.line);
	free(g_sh.line);
	if (found)
	{
		print_prompt();
		write_term(found, g_sh.prompt.len);
		g_sh.line = ft_strnew();
		ft_strspush(&g_sh.line, found);
		g_sh.l = (unsigned short)ft_strlen(found);
	}
	else
	{
		error("no match found", 0);
		print_prompt();
		g_sh.line = ft_strnew();
		g_sh.l = 0;
	}
}

void			research_history(void)
{
	t_prompt	prompt_save;

	validate_line();
	free(g_sh.line);
	prompt_save = g_sh.prompt;
	change_prompt(H_R_P, "\x1b[0m", ':');
	print_prompt();
	retrieve_input();
	del_prompt();
	g_sh.prompt = prompt_save;
	reverse_search();
}
