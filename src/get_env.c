/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfontani <tfontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 15:00:46 by tfontani          #+#    #+#             */
/*   Updated: 2017/02/09 16:57:34 by tfontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "sh.h"

#include "libft.h"

char	*get_env(const char *name)
{
	char			**env;
	unsigned int	strlen;

	env = g_sh.env;
	strlen = ft_strlen(name);
	while (*env && (ft_strncmp(name, *env, strlen) || (*env)[strlen] != '='))
		++env;
	return (*env) ? *env + strlen + 1 : (char*)0;
}
