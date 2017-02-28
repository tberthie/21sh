/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfontani <tfontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 14:13:25 by tfontani          #+#    #+#             */
/*   Updated: 2017/02/13 10:58:35 by tfontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

unsigned char	setup(void);
int				quit(void);

void			change_prompt(char *prompt, char *color, char after_color);
void			del_prompt(void);

void			set_term_cols(void);

void			set_prompt_cwd(void);

void			set_path(void);

#endif
