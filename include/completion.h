/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 19:53:50 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/20 19:53:51 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPLETION_H
# define COMPLETION_H

typedef struct	s_completion
{
	char			*str;
	char			**dc;
	char			**match;
	char			*dir;
	unsigned short	beg;
	unsigned short	end;
	unsigned char	type;
	char			padding[3];
}				t_completion;

enum	e_completion_type
{
	CT_SIMPLE_FILE,
	CT_SIMPLE_COMMAND
};

void			completion(void);

void			completion_ls(char **match);

void			retrieve_completion_info(t_completion *c);

void			completion_simple_file(t_completion *c);
void			completion_simple_command(t_completion *c);
void			completion_simple_complete(t_completion *c);

#endif
