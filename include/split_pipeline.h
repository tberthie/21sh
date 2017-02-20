/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 16:18:22 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/20 19:54:53 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPLIT_PIPELINE_H
# define SPLIT_PIPELINE_H

# include "parse_exec.h"

char			split_pipeline(char **pipes, t_exec *exec);

#endif
