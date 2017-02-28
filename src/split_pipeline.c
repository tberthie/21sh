/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfontani <tfontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 19:55:24 by tfontani          #+#    #+#             */
/*   Updated: 2017/02/20 19:55:25 by tfontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "split_pipeline.h"

#include "libft.h"
#include "error.h"
#include "parse_redirs.h"
#include "replace_parameters.h"

char			split_pipeline(char **pipes, t_exec *exec)
{
	char		**args;
	char		status;

	status = 0;
	while (!status && *pipes)
		if (!(status = parse_redirs(*pipes, exec)))
		{
			while (**pipes == ' ' || **pipes == '\t')
				(*pipes)++;
			*pipes = replace_alias(*pipes);
			args = (char**)ft_parrnew();
			ft_parrpush((void***)&args, ft_strdup(*pipes));
			ft_parrpush((void***)&exec->args, args);
			if (!*pipes++)
			{
				error("bad command syntax", 0);
				return (ERROR);
			}
		}
	return (status);
}
