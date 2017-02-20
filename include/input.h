/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 19:54:19 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/20 19:54:21 by tberthie         ###   ########.fr       */
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

#endif
