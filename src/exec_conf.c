/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_conf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfontani <tfontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 17:36:22 by tfontani          #+#    #+#             */
/*   Updated: 2017/02/18 18:30:58 by tfontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "sh.h"

#include "libft.h"

#include <stdlib.h>
#include <fcntl.h>

void	exec_pipes_init(t_exec *exec, t_exec_process *ep)
{
	unsigned int	nb_cmds;

	nb_cmds = ft_parrlen((void**)exec->args);
	ep->names = ft_m(sizeof(char*) * nb_cmds);
	ep->ids = ft_m(sizeof(pid_t) * nb_cmds);
	ep->pipes = ft_m(sizeof(int) * (nb_cmds - 1) * 2);
}

void	exec_pre_conf(void)
{
	tcsetattr(STDIN_FILENO, TCSADRAIN, g_sh.term_conf);
}

void	exec_post_conf(void)
{
	struct termios	term_conf;

	term_conf = *(struct termios*)g_sh.term_conf;
	term_conf.c_lflag &= (tcflag_t)(~(ICANON | ECHO));
	tcsetattr(STDIN_FILENO, TCSADRAIN, &term_conf);
}
