/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfontani <tfontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 14:05:38 by tfontani          #+#    #+#             */
/*   Updated: 2017/02/28 14:05:40 by tfontani         ###   ########.fr       */
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
