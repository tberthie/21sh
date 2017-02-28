/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 16:20:47 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/28 16:20:49 by tberthie         ###   ########.fr       */
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
