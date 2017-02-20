/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 19:56:37 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/20 19:56:38 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

#include "libft.h"

#include <unistd.h>
#include <fcntl.h>

static void		redir_to_file(t_redirection *redir, int ***restore)
{
	int		*fds;
	int		fd;

	fds = (int*)ft_m(sizeof(int) * 3);
	fds[0] = dup(redir->fd_src);
	fds[1] = redir->fd_src;
	if ((fd = open(redir->s, O_WRONLY | O_CREAT
	| ((redir->type == OUT) ? O_TRUNC : O_APPEND),
	S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) != -1)
		dup2(fd, redir->fd_src);
	fds[2] = fd;
	ft_parrpush((void***)restore, fds);
}

static void		redir_from_file(t_redirection *redir, int ***restore)
{
	int		*fds;
	int		fd;

	fds = (int*)ft_m(sizeof(int) * 3);
	fds[0] = dup(redir->fd_src);
	fds[1] = redir->fd_src;
	if ((fd = open(redir->s, O_RDONLY)) != -1)
		dup2(fd, redir->fd_src);
	fds[2] = fd;
	ft_parrpush((void***)restore, fds);
}

static void		heredoc(t_redirection *redir, int ***restore)
{
	int		*fds;
	int		pfd[2];

	fds = (int*)ft_m(sizeof(int) * 3);
	fds[0] = dup(redir->fd_src);
	fds[1] = redir->fd_src;
	pipe(pfd);
	dup2(pfd[0], redir->fd_src);
	write(pfd[1], redir->s, ft_strlen(redir->s));
	close(pfd[1]);
	fds[2] = -1;
	ft_parrpush((void***)restore, fds);
}

static void		redir_dup(t_redirection *redir, int ***restore)
{
	int		*fds;
	int		fd;

	fds = (int*)ft_m(sizeof(int) * 3);
	fds[0] = dup(redir->fd_src);
	fds[1] = redir->fd_src;
	fd = *redir->s == '-' ? -1 : ft_atoi(redir->s);
	if (fd == -1)
		close(redir->fd_src);
	else if (fd != redir->fd_src)
		dup2(fd, redir->fd_src);
	fds[2] = -1;
	ft_parrpush((void***)restore, fds);
}

int				**treat_redirs(t_redirection **redirs)
{
	int		**restore;

	restore = (int**)ft_parrnew();
	if ((*redirs)->type != NONE)
		while (*redirs)
		{
			if ((*redirs)->type == OUT || (*redirs)->type == APP)
				redir_to_file(*redirs, &restore);
			if ((*redirs)->type == IN)
				redir_from_file(*redirs, &restore);
			if ((*redirs)->type == HERE)
				heredoc(*redirs, &restore);
			if ((*redirs)->type == DUP_IN || (*redirs)->type == DUP_OUT)
				redir_dup(*redirs, &restore);
			++redirs;
		}
	return (restore);
}
