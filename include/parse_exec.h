/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 16:21:31 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/28 16:21:33 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_EXEC_H
# define PARSE_EXEC_H

# define INPUT	1
# define ERROR	2

# include "execution.h"

t_exec			**parse_exec(char *line);

#endif
