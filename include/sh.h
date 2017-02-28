/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfontani <tfontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 14:44:13 by tfontani          #+#    #+#             */
/*   Updated: 2017/02/27 12:13:20 by tfontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

# include <termios.h>

typedef struct	s_prompt
{
	unsigned char	len;
	char			after_col;
	char			padding[6];
	char			*str;
	char			*col;
}				t_prompt;

typedef struct	s_hash
{
	char			*cmd;
	char			*path;

	struct s_hash	*next;
}				t_hash;

typedef struct	s_sh
{
	char			*line;

	char			**env;
	char			**path;

	t_hash			*hash_table;

	char			**locales;

	char			**history;

	char			*pwd;
	char			*oldpwd;

	char			*home;

	t_prompt		prompt;

	char			*clipboard;

	char			**alias_k;
	char			**alias_v;

	unsigned short	l;
	unsigned short	h;

	unsigned short	term_cols;

	unsigned char	last_ret;

	unsigned char	is_running;
	unsigned char	is_inputting;

	unsigned char	is_sourcing;

	unsigned char	interrupted;

	char			pad[5];

	void			*term_conf;
	const char		*term_env;
}				t_sh;

extern t_sh		g_sh;

#endif
