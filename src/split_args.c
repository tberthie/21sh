/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfontani <tfontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 14:03:41 by tfontani          #+#    #+#             */
/*   Updated: 2017/02/28 14:03:42 by tfontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "split_args.h"

#include "libft.h"
#include "globbing.h"

static void		backslash(char **pipe, char **word, char quote)
{
	(*pipe)++;
	if (quote && **pipe == 'n')
		ft_strpush(word, '\n');
	else if (quote && **pipe == 't')
		ft_strpush(word, '\t');
	else
		ft_strpush(word, **pipe);
	(*pipe)++;
}

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
			else
				*pipe == '\\' ? backslash(&pipe, &word, quote) :
				ft_strpush(&word, *pipe++);
		ft_parrpush((void***)&args, word);
		while (*pipe == ' ' || *pipe == '\t')
			pipe++;
	}
	args = globbing(args);
	return (args);
}
