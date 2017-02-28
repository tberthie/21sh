/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 16:28:41 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/28 16:28:42 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

#include "libft.h"

unsigned char	echo(char **args)
{
	unsigned char	newline;

	newline = (*args && !ft_strcmp(*args, "-n"));
	args += newline;
	while (*args)
	{
		ft_putstr(*args++);
		if (*args)
			ft_putchar(' ');
	}
	if (!newline)
		ft_putchar('\n');
	return (0);
}
