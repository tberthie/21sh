/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 17:18:26 by tberthie          #+#    #+#             */
/*   Updated: 2017/03/01 13:26:10 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execution.h>
#include <sh.h>

#include <libft.h>

#include <stdlib.h>

static unsigned char	get_hash_key(char *cmd)
{
	unsigned char	key;

	key = 0;
	while (*cmd)
		key += (unsigned char)*cmd++;
	return (key);
}

char					*hash_table_get(char *cmd)
{
	unsigned char	key;
	t_hash			*hash;

	key = get_hash_key(cmd);
	if (g_sh.hash_table[key].cmd)
	{
		if (!ft_strcmp(cmd, g_sh.hash_table[key].cmd))
			return (ft_strdup(g_sh.hash_table[key].path));
		hash = g_sh.hash_table + key;
		while ((hash = hash->next) && ft_strcmp(cmd, hash->cmd))
			;
		if (hash)
			return (ft_strdup(hash->path));
	}
	return ((char*)0);
}

char					*hash_table_set(char *cmd, char *path)
{
	t_hash			*hash;

	hash = g_sh.hash_table + get_hash_key(cmd);
	if (hash->cmd)
	{
		while (hash->next)
			hash = hash->next;
		hash->next = ft_m(sizeof(t_hash));
		hash = hash->next;
	}
	hash->cmd = ft_strdup(cmd);
	hash->path = ft_strdup(path);
	hash->next = 0;
	return (path);
}
