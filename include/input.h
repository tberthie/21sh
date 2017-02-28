/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 16:21:16 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/28 16:21:18 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

void	print_prompt(void);
void	input(void);
void	validate_line(void);
void	input_again(char *prompt);

void	retrieve_input(void);

char	*heredoc(char *key);

void	treat_char(char c);

void	move_cursor(unsigned short c, short shift);
void	write_term(char *str, unsigned short c);
void	clear_line(void);
void	check_cursor_pos(void);

#endif
