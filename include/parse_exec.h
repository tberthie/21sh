/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfontani <tfontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 14:05:43 by tfontani          #+#    #+#             */
/*   Updated: 2017/02/28 14:05:44 by tfontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_EXEC_H
# define PARSE_EXEC_H

# define INPUT	1
# define ERROR	2

# include "execution.h"

t_exec			**parse_exec(char *line);

#endif
