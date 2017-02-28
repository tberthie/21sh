/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 16:22:15 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/28 16:22:19 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMCAP_H
# define TERMCAP_H

void	perform_termcap(char *str);
void	perform_termcap_nb(char *str, unsigned short nb);

# define T_CM_LEFT "le"
# define T_CM_RIGHT "nd"
# define T_CM_UP "sr"
# define T_CM_DOWN "sf"

#endif
