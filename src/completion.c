/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfontani <tfontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 14:49:42 by tfontani          #+#    #+#             */
/*   Updated: 2017/02/07 17:55:43 by tfontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"
#include "sh.h"

#include "libft.h"

#include <stdlib.h>

void			completion(void)
{
	t_completion	c;

	retrieve_completion_info(&c);
	if (c.dc)
	{
		c.match = (char**)ft_parrnew();
		if (c.type == CT_SIMPLE_FILE)
			completion_simple_file(&c);
		else if (c.type == CT_SIMPLE_COMMAND)
			completion_simple_command(&c);
		ft_parrfree((void**)c.dc);
		free(c.match);
	}
	free(c.str);
	free(c.dir);
}
