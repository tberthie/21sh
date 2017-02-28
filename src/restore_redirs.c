/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_redirs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 17:19:11 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/28 17:19:11 by tberthie         ###   ########.fr       */
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
