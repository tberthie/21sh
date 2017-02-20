/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 19:53:35 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/20 19:53:37 by tberthie         ###   ########.fr       */
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

unsigned char	source(char *arg);

#endif
