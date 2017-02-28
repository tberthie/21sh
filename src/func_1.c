/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 17:18:13 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/28 17:18:16 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "func.h"
#include "sh.h"
#include "input.h"

#include "libft.h"

#include <stdlib.h>

void	func_mv_cu_be(void)
{
	move_cursor(g_sh.prompt.len + g_sh.l, -(short)g_sh.l);
	g_sh.l = 0;
}

void	func_mv_cu_af(void)
{
	move_cursor(g_sh.prompt.len + g_sh.l, (short)ft_strlen(g_sh.line) - g_sh.l);
	g_sh.l = (unsigned short)ft_strlen(g_sh.line);
}

void	func_cl_bf_cu(void)
{
	char	*str;

	free(g_sh.clipboard);
	clear_line();
	str = ft_strnew();
	ft_strspush(&str, g_sh.line + g_sh.l);
	g_sh.line[g_sh.l] = '\0';
	g_sh.clipboard = ft_strdup(g_sh.line);
	free(g_sh.line);
	g_sh.line = str;
	write_term(str, g_sh.prompt.len);
	move_cursor(g_sh.prompt.len + (unsigned short)ft_strlen(str),
		-(short)ft_strlen(str));
	g_sh.l = 0;
}

void	func_copy(void)
{
	free(g_sh.clipboard);
	g_sh.clipboard = ft_strdup(g_sh.line);
}

void	func_paste(void)
{
	ft_strsins(&g_sh.line, g_sh.clipboard, g_sh.l);
	write_term(g_sh.line + g_sh.l, g_sh.prompt.len + g_sh.l);
	g_sh.l += (unsigned short)ft_strlen(g_sh.clipboard);
	move_cursor((unsigned short)ft_strlen(g_sh.line)
		+ g_sh.prompt.len, g_sh.l - (short)ft_strlen(g_sh.line));
}
