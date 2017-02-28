/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfontani <tfontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 16:33:11 by tfontani          #+#    #+#             */
/*   Updated: 2017/01/25 16:52:25 by tfontani         ###   ########.fr       */
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
