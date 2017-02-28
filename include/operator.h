/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 16:21:24 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/28 16:21:26 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATOR_H
# define OPERATOR_H

enum				e_ops
{
	CMD,
	SEP,
	AND,
	OR
};

char				*operator_str(unsigned char op);
char				*operator_name(unsigned char op);
unsigned char		operator_id(char *line);
unsigned char		redir_id(char *line);

#endif
