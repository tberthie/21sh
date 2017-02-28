/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 17:19:32 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/28 17:19:33 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "sh.h"

#include <sys/ioctl.h>

void	set_term_cols(void)
{
	struct winsize	w;

	if (!ioctl(0, TIOCGWINSZ, &w))
		g_sh.term_cols = w.ws_col;
}
