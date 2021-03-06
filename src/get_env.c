/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 17:18:21 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/28 17:18:22 by tberthie         ###   ########.fr       */
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
