/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfontani <tfontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 16:37:00 by tfontani          #+#    #+#             */
/*   Updated: 2017/02/28 14:21:51 by tfontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "sh.h"
#include "parse.h"
#include "func.h"
#include "config.h"
#include "def.h"

#include "libft.h"

#include <stdlib.h>
#include <unistd.h>

static void		process_cmd(void)
{
	add_to_history(g_sh.line);
	exec_cmd(g_sh.line);
}

static void		check_exec(void)
{
	unsigned int	i;

	i = ft_strlen(g_sh.line);
	if (!i || g_sh.line[i - 1] != '\\'
	|| (i > 1 && g_sh.line[i - 2] == '\\'))
		process_cmd();
	else
	{
		g_sh.line[i - 1] = '\0';
		input_again("");
	}
}

void			input(void)
{
	print_prompt();
	retrieve_input();
	check_exec();
}

void			validate_line(void)
{
	ft_putnchar('\n', (ft_strlen(g_sh.line) + g_sh.prompt.len) / g_sh.term_cols
		- (g_sh.l + g_sh.prompt.len) / g_sh.term_cols + 1);
}

void			input_again(char *prompt)
{
	char			*line;
	t_prompt		prompt_save;

	prompt_save = g_sh.prompt;
	change_prompt(prompt, PROMPT_COLOR_W, '>');
	print_prompt();
	line = g_sh.line;
	retrieve_input();
	if (!g_sh.interrupted)
		ft_freeswap((void**)&g_sh.line,
			(!ft_strcmp("quote", prompt) || !ft_strcmp("dquote", prompt)) ?
			ft_strsjoin(line, g_sh.line, "\\n") : ft_strjoin(line, g_sh.line));
	else
		g_sh.interrupted = 0;
	del_prompt();
	g_sh.prompt = prompt_save;
	free(line);
	check_exec();
}
