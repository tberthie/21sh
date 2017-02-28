/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfontani <tfontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 17:13:49 by tfontani          #+#    #+#             */
/*   Updated: 2017/02/13 11:07:57 by tfontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "sh.h"
#include "config.h"

#include "libft.h"

#include <stdlib.h>

void	env_check(char *var)
{
	char	*ptr;

	if (!ft_strncmp("PATH=", var, 5))
	{
		ft_parrfree((void**)g_sh.path);
		set_path();
	}
	else if (!ft_strncmp("HOME=", var, 5))
	{
		free(g_sh.home);
		del_prompt();
		g_sh.home = ft_strdup(
			(ptr = get_env("HOME")) ? ptr : "");
		set_prompt_cwd();
	}
}
