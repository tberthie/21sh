/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 17:19:34 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/28 17:19:35 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcap.h"
#include "sh.h"

#include "libft.h"

#include <term.h>
#include <unistd.h>

static int	putc(int c)
{
	write(1, &c, 1);
	return (0);
}

void		perform_termcap(char *str)
{
	if ((str = tgetstr(str, (char**)0)))
		tputs(str, 0, putc);
}

void		perform_termcap_nb(char *str, unsigned short nb)
{
	if ((str = tgetstr(str, (char**)0)))
		while (nb--)
			tputs(str, 0, putc);
}
