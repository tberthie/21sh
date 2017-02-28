/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 17:19:05 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/28 17:19:06 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "sh.h"
#include "input.h"
#include "env.h"
#include "def.h"

#include "libft.h"

#include <stdlib.h>

void	set_prompt_cwd(void)
{
	char	*pwd;
	char	*s;

	pwd = ft_strnew();
	if (*g_sh.home && !ft_strncmp(g_sh.home, g_sh.pwd, ft_strlen(g_sh.home)))
	{
		ft_strpush(&pwd, '~');
		ft_strspush(&pwd, g_sh.pwd + ft_strlen(g_sh.home));
	}
	else
		ft_strspush(&pwd, g_sh.pwd);
	if (ft_strlen(pwd) > PROMPT_PWD_LIMIT)
	{
		s = ft_strnew();
		ft_strspush(&s, "...");
		ft_strspush(&s, pwd + ft_strlen(pwd) - PROMPT_PWD_LIMIT + 3);
		free(pwd);
		pwd = s;
	}
	change_prompt(pwd, PROMPT_COLOR, '>');
	free(pwd);
}

void	change_prompt(char *prompt, char *color, char after_color)
{
	g_sh.prompt.len = (unsigned char)ft_strlen(prompt) + 2;
	g_sh.prompt.after_col = after_color;
	g_sh.prompt.col = ft_strdup(color);
	g_sh.prompt.str = ft_strdup(prompt);
}

void	del_prompt(void)
{
	free(g_sh.prompt.str);
	free(g_sh.prompt.col);
}

void	print_prompt(void)
{
	ft_putstr(g_sh.prompt.col);
	write_term(g_sh.prompt.str, 0);
	ft_putstr("\x1b[0m");
	ft_putchar(g_sh.prompt.after_col);
	ft_putchar(' ');
}
