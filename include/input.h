/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfontani <tfontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 16:41:55 by tfontani          #+#    #+#             */
/*   Updated: 2017/02/26 14:59:59 by tfontani         ###   ########.fr       */
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
