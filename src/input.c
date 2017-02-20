/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 19:57:00 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/20 19:57:02 by tberthie         ###   ########.fr       */
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

static unsigned char	check_exec(void)
{
	unsigned int	i;

	i = ft_strlen(g_sh.line);
	if (!i || g_sh.line[i - 1] != '\\'
	|| (i > 1 && g_sh.line[i - 2] == '\\'))
		return (1);
	g_sh.line[ft_strlen(g_sh.line) - 1] = '\0';
	return (0);
}

static void				process_cmd(char *line)
{
	add_to_history(line);
	exec_cmd(line);
}

void					input(void)
{
	print_prompt();
	retrieve_input();
	if (check_exec())
		process_cmd(g_sh.line);
	else
		input_again("");
}

void					validate_line(void)
{
	ft_putnchar('\n', (ft_strlen(g_sh.line) + g_sh.prompt.len) / g_sh.term_cols
		- (g_sh.l + g_sh.prompt.len) / g_sh.term_cols + 1);
}

void					input_again(char *prompt)
{
	char			*line;
	t_prompt		prompt_save;
	unsigned char	exec;

	prompt_save = g_sh.prompt;
	change_prompt(prompt, PROMPT_COLOR_W, '>');
	print_prompt();
	line = g_sh.line;
	retrieve_input();
	exec = check_exec();
	ft_freeswap((void**)&g_sh.line, ft_strjoin(line, g_sh.line));
	free(line);
	if (exec)
		process_cmd(g_sh.line);
	else
		input_again("");
	del_prompt();
	g_sh.prompt = prompt_save;
}
