/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 17:18:29 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/28 17:18:29 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "sh.h"
#include "config.h"

#include "libft.h"

#include <stdlib.h>

char	*heredoc(char *key)
{
	char		*line;
	t_prompt	prompt_save;

	prompt_save = g_sh.prompt;
	change_prompt("heredoc", "\x1b[0m", '>');
	print_prompt();
	line = ft_strnew();
	retrieve_input();
	while (ft_strcmp(key, g_sh.line))
	{
		ft_strspush(&line, g_sh.line);
		free(g_sh.line);
		ft_strpush(&line, '\n');
		print_prompt();
		retrieve_input();
	}
	free(key);
	free(g_sh.line);
	del_prompt();
	g_sh.prompt = prompt_save;
	return (line);
}
