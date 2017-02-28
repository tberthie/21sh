/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_parameters.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfontani <tfontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 14:05:52 by tfontani          #+#    #+#             */
/*   Updated: 2017/02/28 14:05:53 by tfontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLACE_PARAMETERS_H
# define REPLACE_PARAMETERS_H

char		*replace_alias(char *cmd);
void		replace_params(char **cmd, char **line);
void		replace_tilde(char **cmd, char **line);

#endif
