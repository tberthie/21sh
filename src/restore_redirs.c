/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_redirs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfontani <tfontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 19:55:15 by tfontani          #+#    #+#             */
/*   Updated: 2017/02/20 21:37:34 by tfontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

#include "libft.h"

#include <unistd.h>
#include <stdlib.h>

void			restore_redirs(int **fds)
{
	int		**beg;

	beg = fds;
	while (*fds)
	{
		if ((*fds)[2] != -1)
			close((*fds)[2]);
		dup2((*fds)[0], (*fds)[1]);
		close((*fds)[0]);
		fds++;
	}
	ft_parrfree((void**)beg);
}
