/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 16:28:22 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/28 16:28:23 by tberthie         ###   ########.fr       */
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
