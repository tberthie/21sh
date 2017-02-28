/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfontani <tfontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 15:55:29 by tfontani          #+#    #+#             */
/*   Updated: 2017/01/27 14:53:47 by tfontani         ###   ########.fr       */
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
