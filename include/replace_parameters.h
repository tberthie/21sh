/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_parameters.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 16:21:53 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/28 16:21:55 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLACE_PARAMETERS_H
# define REPLACE_PARAMETERS_H

char		*replace_alias(char *cmd);
void		replace_params(char **cmd, char **line);
void		replace_tilde(char **cmd, char **line);

#endif
