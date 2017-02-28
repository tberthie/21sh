/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfontani <tfontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 15:38:59 by tfontani          #+#    #+#             */
/*   Updated: 2017/02/20 15:26:21 by tfontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "error.h"
#include "parse.h"
#include "sh.h"

#include "libft.h"
#include "libft_internal.h"

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static char				*read_content(int fd)
{
	char	*fc;
	char	buf[RFC_READ + 1];
	int		ret;

	fc = ft_strnew();
	while ((ret = (int)read(fd, buf, RFC_READ)) > 0)
	{
		buf[ret] = '\0';
		ft_strspush(&fc, buf);
	}
	if (ret != -1)
		return (fc);
	free(fc);
	return ((char*)0);
}

static void				source_exec_line(char **line, char *ptr, char *fc)
{
	*ptr = '\0';
	ft_strspush(line, fc);
	if (ptr != fc)
	{
		if (ptr[-1] != '\\')
		{
			exec_cmd(*line);
			*line = ft_strnew();
		}
		else
			(*line)[ft_strlen(*line) - 1] = '\0';
	}
}

static void				source_exec_file(char *fc)
{
	char			*line;
	char			*ptr;

	line = ft_strnew();
	while ((ptr = ft_strchr(fc, '\n')))
	{
		source_exec_line(&line, ptr, fc);
		fc = ptr + 1;
	}
	if (*line)
		exec_cmd(line);
	else
		free(line);
}

unsigned char			source(char *arg)
{
	char	*fc;
	int		fd;

	if (arg)
	{
		if ((fd = open(arg, O_RDONLY)) != -1
		&& (fc = read_content(fd)))
		{
			g_sh.is_sourcing = 1;
			source_exec_file(fc);
			free(fc);
			close(fd);
			g_sh.is_sourcing = 0;
			return (0);
		}
		else
			error("source: couldn't read file", arg);
	}
	else
		error("source: not enough arguments", 0);
	return (1);
}
