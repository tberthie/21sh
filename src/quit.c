/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 19:57:28 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/20 19:57:29 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "sh.h"

#include "libft.h"

#include <stdlib.h>
#include <term.h>
#include <unistd.h>

int		quit(void)
{
	if (tcsetattr(STDIN_FILENO, TCSADRAIN, (struct termios*)g_sh.term_conf)
	|| tgetent((char*)0, g_sh.term_env) != 1)
		return (-1);
	ft_parrfree((void**)g_sh.env);
	ft_parrfree((void**)g_sh.path);
	ft_parrfree((void**)g_sh.history);
	ft_parrfree((void**)g_sh.alias_k);
	ft_parrfree((void**)g_sh.alias_v);
	free(g_sh.pwd);
	free(g_sh.oldpwd);
	free(g_sh.home);
	del_prompt();
	free(g_sh.clipboard);
	return (0);
}
