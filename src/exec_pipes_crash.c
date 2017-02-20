/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes_crash.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 19:56:35 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/20 19:56:36 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execution.h>
#include <error.h>

#include <libft.h>

#include <stdlib.h>

void	pipes_crash_push(t_pipecrash ***pipecrashes, char *bin,
							unsigned char signal)
{
	t_pipecrash		*pc;

	pc = ft_m(sizeof(t_pipecrash));
	pc->name = bin;
	pc->signal = signal;
	if (!*pipecrashes)
		*pipecrashes = (t_pipecrash**)ft_parrnew();
	ft_parrpush((void***)pipecrashes, pc);
}

void	pipes_crash_print(t_pipecrash **pipecrashes)
{
	unsigned int	i;

	i = 0;
	while (pipecrashes[i])
	{
		print_exit_signal(pipecrashes[i]->signal, pipecrashes[i]->name);
		free(pipecrashes[i++]);
	}
	free(pipecrashes);
}
