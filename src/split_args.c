/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 17:31:48 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/20 19:57:50 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "split_args.h"

#include "libft.h"
#include "globbing.h"

char			**split_args(char *pipe)
{
	char		**args;
	char		*word;
	char		quote;

	quote = 0;
	args = (char**)ft_parrnew();
	while (*pipe == ' ' || *pipe == '\t')
		pipe++;
	while (*pipe)
	{
		word = ft_strnew();
		while (*pipe && ((*pipe != ' ' && *pipe != '\t') || quote))
			if ((*pipe == '\'' || *pipe == '"') && !quote)
				quote = *pipe++;
			else if (*pipe == quote)
				quote -= *pipe++;
			else if ((pipe += *pipe == '\\'))
				ft_strpush(&word, *pipe++);
		ft_parrpush((void***)&args, word);
		while (*pipe == ' ' || *pipe == '\t')
			pipe++;
	}
	args = globbing(args);
	return (args);
}
