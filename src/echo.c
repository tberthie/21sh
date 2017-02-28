/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfontani <tfontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 19:53:20 by tfontani          #+#    #+#             */
/*   Updated: 2017/02/20 19:53:21 by tfontani         ###   ########.fr       */
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
