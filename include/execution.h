/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfontani <tfontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 14:05:30 by tfontani          #+#    #+#             */
/*   Updated: 2017/02/28 14:05:32 by tfontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <unistd.h>

enum		e_redirs
{
	NONE,
	IN,
	OUT,
	APP,
	HERE,
	DUP_IN,
	DUP_OUT,
};

typedef struct	s_redirection
{
	unsigned char	type;
	char			padding[3];

	int				fd_src;
	char			*s;
}				t_redirection;

typedef struct	s_exec
{
	char			***args;
	char			**paths;

	unsigned char	id;
	char			padding[7];

	t_redirection	***redirs;
}				t_exec;

typedef struct	s_exec_process
{
	char	**names;
	pid_t	*ids;
	int		*pipes;
}				t_exec_process;

void			exec(t_exec *exec);
void			exec_pre_conf(void);
void			exec_post_conf(void);

void			launch_cmd(t_exec *exec) __attribute__((noreturn));
int				**treat_redirs(t_redirection **redirs, unsigned char save);
void			restore_redirs(int	**fds);

void			exec_pipes(t_exec *exec);
void			exec_pipes_init(t_exec *exec, t_exec_process *ep);
void			next_pipe(t_exec *exec, int *pipefd) __attribute__((noreturn));

typedef struct	s_pipecrash
{
	char			*name;

	unsigned char	signal;
	char			padding[7];
}				t_pipecrash;

void			pipes_crash_push(t_pipecrash ***pipecrashes, char *bin,
									unsigned char signal);
void			pipes_crash_print(t_pipecrash **pipecrashes);

char			**find_exec_paths(char ***args);

char			*hash_table_get(char *cmd);
char			*hash_table_set(char *cmd, char *path);

#endif
