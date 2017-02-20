/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 19:57:42 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/20 19:57:43 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"
#include "sh.h"
#include "config.h"
#include "termcap.h"
#include "input.h"
#include "execution.h"

#include "libft.h"

#include <stdio.h>
#include <stdlib.h>

void	sig_handle(int signal)
{
	if (signal == 2 && g_sh.is_inputting)
	{
		free(g_sh.line);
		validate_line();
		print_prompt();
		g_sh.l = 0;
		g_sh.h = (unsigned short)ft_parrlen((void*)g_sh.history);
		g_sh.line = ft_strnew();
	}
}

void	sig_resize(int signal)
{
	unsigned short	prev_cols;

	(void)signal;
	prev_cols = g_sh.term_cols;
	set_term_cols();
}

void	sig_suspend(int signal)
{
	if (signal == 19)
		exec_post_conf();
}
