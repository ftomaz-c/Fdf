/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:03:31 by ftomaz-c          #+#    #+#             */
/*   Updated: 2023/11/23 15:52:08 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

int	found_newline(char *stash)
{
	int	i;

	i = 0;
	if (stash == NULL)
		return (0);
	while (stash[i] != '\0')
	{
		if (stash[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	stasher(char **stash, char	*buffer)
{
	char	*temp;

	temp = NULL;
	if (*stash)
	{
		temp = ft_strjoin(*stash, buffer);
		free(*stash);
		*stash = temp;
	}
	else
		*stash = ft_strdup(buffer);
}
