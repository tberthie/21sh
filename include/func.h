/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 16:21:11 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/28 16:21:12 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNC_H
# define FUNC_H

void	func_clear(void);
void	func_delete(unsigned char back);
void	func_cursor(signed char shift);

void	func_shortcut(char c);

void	func_ctrl_d(void);

void	func_mv_cu_be(void);
void	func_mv_cu_af(void);
void	func_cl_bf_cu(void);
void	func_mv_wo(signed short shift);

void	func_copy(void);
void	func_paste(void);

void	add_to_history(char *line);
void	navigate_history(signed char shift);
void	research_history(void);

#endif
