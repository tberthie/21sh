/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 19:54:04 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/20 19:54:06 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

static char		*g_sigs[] =
{
	"null",
	"(HANG UP) instruction",
	"^C",
	"(QUIT) instruction",
	"illegal instruction",
	"trace trap",
	"(ABORT) instruction",
	"bus error",
	"floating point exception",
	"(KILL) instruction",
	"user signal 1",
	"segfault",
	0
};

void			error(char *msg, char *name);
void			parse_error(char op);
void			print_exit_signal(unsigned char sig, char *bin);

#endif
