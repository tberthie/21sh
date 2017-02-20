/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_parameters.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 13:32:14 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/20 19:57:31 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "replace_parameters.h"
#include "libft.h"
#include "env.h"
#include "def.h"
#include "sh.h"

#include <unistd.h>
#include <stdlib.h>

static void		param_env(char **cmd, char **line)
{
	char	*env;
	char	*value;

	env = ft_strnew();
	while (**line && **line != ' ' && **line != '\t' && **line != '\'' &&
	**line != '"' && **line != '\\'
	&& **line != '$')
		ft_strpush(&env, *(*line)++);
	if ((value = get_env(env)))
		ft_strspush(cmd, value);
	free(env);
}

static char		param_spe(char **cmd, char *line)
{
	char	*tmp;

	if (*line == '?')
	{
		ft_strspush(cmd, (tmp = ft_itoa(g_sh.last_ret)));
		free(tmp);
	}
	else if (*line == '0')
		ft_strspush(cmd, SH_NAME);
	else if (*line == '$')
	{
		ft_strspush(cmd, (tmp = ft_itoa(getpid())));
		free(tmp);
	}
	else
		return (0);
	return (1);
}

void			replace_params(char **cmd, char **line)
{
	(*line)++;
	if (!**line || **line == ' ' || **line == '\t' || **line == '"' ||
	**line == '\'' || **line == '\\')
		ft_strpush(cmd, '$');
	if (param_spe(cmd, *line))
		(*line)++;
	else
		param_env(cmd, line);
}

char			*replace_alias(char *cmd)
{
	char	*word;
	int		i;
	int		pos;

	i = 0;
	word = ft_strnew();
	while (cmd[i] && cmd[i] != ' ' && cmd[i] != '\t')
		ft_strpush(&word, cmd[i++]);
	pos = ft_strarrstr(g_sh.alias_k, word);
	free(word);
	if (pos != -1)
	{
		word = ft_strjoin(g_sh.alias_v[pos], &cmd[i]);
		free(cmd);
		return (word);
	}
	return (cmd);
}

void			replace_tilde(char **cmd, char **line)
{
	char	*tilde;

	(*line)++;
	if ((tilde = get_env("HOME")))
		ft_strspush(cmd, tilde);
	else
		ft_strpush(cmd, '~');
}
