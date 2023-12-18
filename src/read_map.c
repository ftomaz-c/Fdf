/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:13:48 by ftomaz-c          #+#    #+#             */
/*   Updated: 2023/12/14 23:14:10 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	alloc_mem_matrix(char *file_name, t_data *data)
{
	int		fd;
	char	*line;
	int		i;

	if ((fd = open(file_name, O_RDONLY, 0)) <= 0)
	{
		perror("File does not exist");
		exit(EXIT_FAILURE);
	}
	data->width = count_words((line = get_next_line(fd)), " ");
	free(line);
	data->height = 1;
	while ((line = get_next_line(fd)) != 0)
	{
		data->height++;
		free(line);
	}
	free(line);
	close (fd);
	data->matrix = ft_calloc(sizeof(int *), data->height);
	i = 0;
	while (i < data->height)
	{
		data->matrix[i] = ft_calloc(sizeof(int), data->width);
		i++;
	}
}

void	read_map(char *file_name, t_data *data)
{
	int		fd;
	char	*line;
	char	**split;
	int		x;
	int		y;

	alloc_mem_matrix(file_name, data);
	if ((fd = open(file_name, O_RDONLY, 0)) <= 0)
	{
		perror("File does not exist");
		exit(EXIT_FAILURE);
	}
	y = 0;
	while ((line = get_next_line(fd)) != 0)
	{
		split = ft_split(line, " ");
		x = 0;
		while (split[x])
		{
			data->matrix[y][x] = ft_atoi(split[x]);
			free(split[x]);
			x++;
		}
		free(split);
		free(line);
		y++;
	}
	free(line);
}
