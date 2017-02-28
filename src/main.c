/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfontani <tfontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 14:14:36 by tfontani          #+#    #+#             */
/*   Updated: 2017/02/27 11:01:48 by tfontani         ###   ########.fr       */
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
