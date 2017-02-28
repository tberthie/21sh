/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfontani <tfontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 19:54:40 by tfontani          #+#    #+#             */
/*   Updated: 2017/02/20 19:54:41 by tfontani         ###   ########.fr       */
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
