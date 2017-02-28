/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 16:21:03 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/28 16:21:04 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

void			error(char *msg, char *name);
void			parse_error(unsigned char op);
void			print_exit_signal(unsigned char sig, char *bin);

#endif
