/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 19:56:07 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/20 19:56:08 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "sh.h"
#include "error.h"

#include "libft.h"

#include <stdlib.h>

static unsigned char	is_builtin(char *cmd)
{
	return (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "alias")
	|| !ft_strcmp(cmd, "unalias") || !ft_strcmp(cmd, "echo")
	|| !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "setenv")
	|| !ft_strcmp(cmd, "unsetenv") || !ft_strcmp(cmd, "source")
	|| !ft_strcmp(cmd, "exit"));
}

static void				check_error(unsigned char exists, char *bin)
{
	if (exists)
	{
		error("permission denied", bin);
		g_sh.last_ret = 126;
	}
	else
	{
		error("command not found", bin);
		g_sh.last_ret = 127;
	}
}

static char				*find_exec_path(char *bin)
{
	char			**path;
	char			*cpath;
	unsigned char	exists;

	exists = 0;
	if (is_builtin(bin))
		return (ft_strdup(""));
	if (!ft_strchr(bin, '/'))
	{
		path = g_sh.path;
		while (*path)
		{
			cpath = ft_strcjoin(*path++, bin, '/');
			if (!exists)
				exists = (access(cpath, F_OK) != -1);
			if (access(cpath, X_OK) != -1)
				return (cpath);
			free(cpath);
		}
	}
	else if ((exists = access(bin, F_OK) != -1) && access(bin, X_OK) != -1)
		return (ft_strdup(bin));
	check_error(exists, bin);
	return ((char*)0);
}

char					**find_exec_paths(char ***args)
{
	char		**paths;
	char		*path;

	paths = (char**)ft_parrnew();
	while (*args)
	{
		if ((path = find_exec_path(**args)))
			ft_parrpush((void***)&paths, path);
		else
		{
			ft_parrfree((void**)paths);
			return ((char**)0);
		}
		++args;
	}
	return (paths);
}
