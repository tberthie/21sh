/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 17:18:59 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/28 17:19:01 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "env.h"
#include "sh.h"

#include "libft.h"

void	set_path(void)
{
	char	*path;
	char	*ptr;

	g_sh.path = (char**)ft_parrnew();
	if ((path = get_env("PATH")))
	{
		while ((ptr = ft_strchr(path, ':')))
		{
			*ptr = '\0';
			ft_parrpush((void***)&g_sh.path, ft_strdup(path));
			*ptr = ':';
			path = ptr + 1;
		}
		if (*path)
			ft_parrpush((void***)&g_sh.path, ft_strdup(path));
	}
}
