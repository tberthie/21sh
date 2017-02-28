/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 16:29:19 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/28 16:29:20 by tberthie         ###   ########.fr       */
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
	|| !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset")
	|| !ft_strcmp(cmd, "locals") || !ft_strcmp(cmd, "exit"));
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
	path = g_sh.path;
	if (!ft_strchr(bin, '/'))
		if ((cpath = hash_table_get(bin)))
			return (cpath);
		else
			while (*path)
			{
				cpath = ft_strcjoin(*path++, bin, '/');
				exists = (!exists) ? (access(cpath, F_OK) != -1) : exists;
				if (access(cpath, X_OK) != -1)
					return (hash_table_set(bin, cpath));
				free(cpath);
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
