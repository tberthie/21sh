/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfontani <tfontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 14:05:41 by tfontani          #+#    #+#             */
/*   Updated: 2017/02/28 14:05:42 by tfontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "execution.h"

void				exec_cmd(char *line);
void				free_execs(t_exec **execs);

#endif
