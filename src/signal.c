/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 17:19:23 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/28 17:19:24 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"
#include "sh.h"
#include "config.h"
#include <termcap.h>
#include <input.h>
#include <execution.h>

#include <libft.h>

#include <stdlib.h>

void	sig_handle(int signal)
{
	unsigned short	prev_cols;

	if (signal == 2 && g_sh.is_inputting)
	{
		free(g_sh.line);
		del_prompt();
		g_sh.interrupted = 1;
		set_prompt_cwd();
		validate_line();
		print_prompt();
		g_sh.l = 0;
		g_sh.h = (unsigned short)ft_parrlen((void*)g_sh.history);
		g_sh.line = ft_strnew();
	}
	else if (signal == 19)
		exec_post_conf();
	else if (signal == 28)
	{
		prev_cols = g_sh.term_cols;
		set_term_cols();
	}
}
