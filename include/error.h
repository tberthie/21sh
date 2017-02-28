/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfontani <tfontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 14:05:28 by tfontani          #+#    #+#             */
/*   Updated: 2017/02/28 14:05:29 by tfontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

void			error(char *msg, char *name);
void			parse_error(unsigned char op);
void			print_exit_signal(unsigned char sig, char *bin);

#endif
