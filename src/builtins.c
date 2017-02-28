/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 16:27:53 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/28 16:27:54 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "builtins.h"

#include "libft.h"

void	builtins(char **args)
{
	if (!ft_strcmp(*args, "cd"))
		g_sh.last_ret = cd(args[1]);
	else if (!ft_strcmp(*args, "alias"))
		g_sh.last_ret = alias(args + 1);
	else if (!ft_strcmp(*args, "unalias"))
		g_sh.last_ret = unalias(args + 1);
	else if (!ft_strcmp(*args, "echo"))
		g_sh.last_ret = echo(args + 1);
	else if (!ft_strcmp(*args, "env"))
		g_sh.last_ret = env(args + 1);
	else if (!ft_strcmp(*args, "locals"))
		g_sh.last_ret = locals(args + 1);
	else if (!ft_strcmp(*args, "export"))
		g_sh.last_ret = builtin_export(args + 1);
	else if (!ft_strcmp(*args, "unset"))
		g_sh.last_ret = unset(args + 1);
	else if (!ft_strcmp(*args, "setenv"))
		g_sh.last_ret = builtin_setenv(args + 1);
	else if (!ft_strcmp(*args, "unsetenv"))
		g_sh.last_ret = unset_env(args + 1);
	else if (!ft_strcmp(*args, "source"))
		g_sh.last_ret = source(args[1]);
	else if (!ft_strcmp(*args, "exit"))
		g_sh.is_running = 0;
}
