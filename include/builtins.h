/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfontani <tfontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 14:05:18 by tfontani          #+#    #+#             */
/*   Updated: 2017/02/28 14:05:19 by tfontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

void			builtins(char **args);

unsigned char	cd(char *arg);

unsigned char	alias(char **args);
unsigned char	unalias(char **args);

unsigned char	echo(char **args);

unsigned char	env(char **args);
unsigned char	builtin_setenv(char **args);
unsigned char	unset_env(char **args);

unsigned char	locals(char **args);
void			set_local(char *arg);
unsigned char	builtin_export(char **args);
unsigned char	unset(char **args);
char			*get_local(const char *name);

unsigned char	source(char *arg);

#endif
