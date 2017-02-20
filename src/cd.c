/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 19:55:06 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/20 19:55:07 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "sh.h"
#include "error.h"
#include "env.h"
#include "config.h"

#include "libft.h"

#include <stdlib.h>
#include <unistd.h>

static char		*set_var(char *arg)
{
	if (arg)
		return (arg[0] == '-' && !arg[1]) ? g_sh.oldpwd : arg;
	return (g_sh.home);
}

static void		update_env_vars(void)
{
	char	*str;

	str = ft_strjoin("PWD=", g_sh.pwd);
	set_env(str);
	free(str);
	str = ft_strjoin("OLDPWD=", g_sh.oldpwd);
	set_env(str);
	free(str);
}

unsigned char	cd(char *arg)
{
	char	*path;

	path = set_var(arg);
	if (!chdir(path))
	{
		free(g_sh.oldpwd);
		g_sh.oldpwd = g_sh.pwd;
		if (!(g_sh.pwd = getcwd((char*)0, 0)))
		{
			g_sh.pwd = ft_strdup("");
			return (1);
		}
		if (arg && arg[0] == '-' && !arg[1])
		{
			ft_putstr(g_sh.pwd);
			ft_putchar('\n');
		}
		update_env_vars();
		del_prompt();
		set_prompt_cwd();
		return (0);
	}
	error("couldn't change directory", path);
	return (1);
}
