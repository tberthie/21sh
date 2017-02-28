/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfontani <tfontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 15:55:54 by tfontani          #+#    #+#             */
/*   Updated: 2017/01/26 16:17:53 by tfontani         ###   ########.fr       */
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
