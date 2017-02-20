/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 19:57:40 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/20 19:57:41 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "sh.h"
#include "signal.h"
#include "env.h"
#include "def.h"
#include "builtins.h"

#include "libft.h"

#include <stdlib.h>
#include <term.h>
#include <unistd.h>

static unsigned char	setup_term_conf(void)
{
	struct termios	term_conf;

	if (!(g_sh.term_env = get_env("TERM")))
		g_sh.term_env = DEF_TERM_ENV;
	if (tgetent((char*)0, g_sh.term_env) != 1
	|| tcgetattr(STDIN_FILENO, &term_conf))
		return (0);
	g_sh.term_conf = ft_m(sizeof(struct termios));
	*(struct termios*)g_sh.term_conf = term_conf;
	term_conf.c_lflag &= (tcflag_t)(~(ICANON | ECHO));
	return (!tcsetattr(STDIN_FILENO, TCSADRAIN, &term_conf));
}

static void				set_sh_lvl(void)
{
	char	*str;
	int		sh_lvl;
	int		i;

	if ((i = ft_strarrstrn(g_sh.env, "SHLVL=", 6)) != -1)
	{
		sh_lvl = ft_atoi(g_sh.env[i] + 6);
		free(g_sh.env[i]);
		str = ft_itoa(sh_lvl + 1);
		g_sh.env[i] = ft_strjoin("SHLVL=", str);
		free(str);
	}
	else
		ft_parrpush((void***)&g_sh.env, ft_strdup("SHLVL=1"));
}

static void				load_rc(void)
{
	char	*str;

	if (*g_sh.home)
	{
		str = ft_strnew();
		ft_strspush(&str, g_sh.home);
		ft_strpush(&str, '/');
		ft_strspush(&str, "."SH_NAME"rc");
		source(str);
		free(str);
	}
}

static void				setup_env_vars_and_so(void)
{
	char	*str;

	str = ft_strjoin("PWD=", g_sh.pwd);
	set_env(str);
	free(str);
	str = ft_strjoin("OLDPWD=", g_sh.oldpwd);
	set_env(str);
	free(str);
	g_sh.last_ret = 0;
	g_sh.is_running = 1;
	g_sh.is_sourcing = 0;
	g_sh.clipboard = ft_strnew();
	g_sh.alias_k = (char**)ft_parrnew();
	g_sh.alias_v = (char**)ft_parrnew();
}

unsigned char			setup(void)
{
	extern char		**environ;

	g_sh.env = ft_strarrdup(environ);
	if (!setup_term_conf()
	|| signal(SIGINT, sig_handle) == SIG_ERR
	|| signal(SIGWINCH, sig_resize) == SIG_ERR
	|| signal(SIGCONT, sig_suspend) == SIG_ERR
	|| !(g_sh.pwd = getcwd((char*)0, 0)))
		return (0);
	g_sh.history = (char**)ft_parrnew();
	g_sh.oldpwd = ft_strdup(g_sh.pwd);
	g_sh.home = ft_strdup(
		(g_sh.home = get_env("HOME")) ? g_sh.home : "");
	set_prompt_cwd();
	set_path();
	set_term_cols();
	setup_env_vars_and_so();
	set_sh_lvl();
	load_rc();
	return (1);
}
