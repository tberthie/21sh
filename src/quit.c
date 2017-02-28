/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfontani <tfontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 14:15:17 by tfontani          #+#    #+#             */
/*   Updated: 2017/02/27 11:01:14 by tfontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <config.h>
#include <sh.h>

#include <libft.h>

#include <stdlib.h>
#include <term.h>
#include <unistd.h>

static void		free_hash_elem(t_hash *hash)
{
	t_hash	*cur;

	free(hash->cmd);
	free(hash->path);
	if (hash->next)
	{
		cur = hash->next;
		while ((hash = cur))
		{
			free(cur->cmd);
			free(cur->path);
			cur = hash->next;
			free(hash);
		}
	}
}

static void		free_hash_table(void)
{
	t_hash			*hash_table;
	unsigned char	i;

	hash_table = g_sh.hash_table;
	i = 0;
	while (i != 255)
	{
		if (hash_table[i].cmd)
			free_hash_elem(hash_table + i);
		++i;
	}
	free(hash_table);
}

int				quit(void)
{
	if (tcsetattr(STDIN_FILENO, TCSADRAIN, (struct termios*)g_sh.term_conf)
	|| tgetent((char*)0, g_sh.term_env) != 1)
		return (-1);
	free_hash_table();
	ft_parrfree((void**)g_sh.env);
	ft_parrfree((void**)g_sh.locales);
	ft_parrfree((void**)g_sh.path);
	ft_parrfree((void**)g_sh.history);
	ft_parrfree((void**)g_sh.alias_k);
	ft_parrfree((void**)g_sh.alias_v);
	free(g_sh.pwd);
	free(g_sh.oldpwd);
	free(g_sh.home);
	del_prompt();
	free(g_sh.clipboard);
	free(g_sh.term_conf);
	return (0);
}
