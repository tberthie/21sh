/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 17:18:43 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/28 17:18:43 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>
#include <config.h>
#include <input.h>

#include <libft.h>

#include <unistd.h>

t_sh	g_sh;

int				main(void)
{
	if (!setup())
		return (-1);
	while (g_sh.is_running)
	{
		input();
		check_cursor_pos();
	}
	return (quit());
}
