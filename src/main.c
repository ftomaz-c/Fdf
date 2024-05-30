/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc < ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:07:28 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/30 18:27:03 by ftomazc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// **	------------------------------------------- How to do -------------------------------------------
// **	1. read file
// **		- get height(how many lines) of text
// **		- get width(how many numbers in line)
// **		- allocate memory for **int by using width and height (look your ft_split() )
// **		- read file and write number into **int matrix
// **				by using ft_split() and atoi()
// **	--------------
// **	2. drawing line function (google Bresenham algorithm)
// **		- find by how much we need to increase x and by how much we need to increase y
// **			by using float. Example:
// **				x = 2; x1 = 4;
// **				y = 2; y1 = 6;
// **				steps for x: 2
// **				steps for y: 4
// **				that means that y should grow 2 times faster than x
// **				every loop step: y += 1 and x += 0.5
// **				after 4 steps x and y will be equal with x1, y1
// **
// **					real x:y		x:y     pixels
// **			start:		2.0 : 2.0		2:2        .
// **			step1:		2.5 : 3.0		2:3        .
// **			step2:		3.0 : 4.0		3:4         .
// **			step3:		3.5 : 5.0		3:5         .
// **			step4:		4.0 : 6.0		4:6          .
// **
// **				that works because (float)2.5 turns to (int)2 in func. mlx_pixel_put()
// **	--------------
// **	3. function which draws lines between every dot
// **		- example:
// **				0->		0->		0->		0
// **				|		|		|		|
// **
// **				0->		10->            10->            0
// **				|		|		|		|
// **
// **				0->		10->            10->            0
// **				|		|		|		|
// **
// **				0->		0->		0->		0
// **			'->' and '|'are lines between dots
// **			every dot has two lines (right and down):	0->
// **                                                                      |
// **	----------------
// **	4. adding 3D
// **		- change coordinates by using isometric formulas:
// **			x` = (x - y) * cos(angle)
// **			y` = (x + y) * sin(angle) - z
// **		- x` and y` are coordinates in 3D format (default angle 0.8)
// **	----------------
// **	5. adding bonuses (move, rotation, zoom)
// **		- when you press button on keyboard the func. mlx_key_hook(win_ptr, deal_key, NULL);
// **			call the func. deal_key.
// **		- In the deal key func. you have to change some parameters, clear the window with
// **			mlx_clear_window(mlx_ptr, win_ptr); and redraw the picture
// **	----------------
// **	6. error handling
// **		- check if argc == 2
// **		- check if file exists: if ((fd = open(file_name, O_RDONLY) > 0))
// **	----------------
// **	7. fix leaks
// **		- type leaks a.out or leaks fdf in your shell


#include "../includes/fdf.h"
#include <stdio.h>

int	get_number(char *line, int start)
{
	int		nbr;

	nbr = 0;
	while (ft_isdigit(line[start]))
	{
		nbr = nbr * 10 + (line[start] - '0');
		start++;
	}
	return (nbr);
}

void get_active_display_size(t_data *data)
{
	Display	*display;
	Screen	*screen;

	display = XOpenDisplay(NULL);
	screen = DefaultScreenOfDisplay(display);
	data->display_size_x = screen->width - 100;
	data->display_size_y = screen->height - 100;
	XCloseDisplay(display);
}

void	free_matrix(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->height)
	{
		free(data->matrix[i]);
		i++;
	}
	free(data->matrix);
}

void	move_matrix(int key, t_data *data)
{
	if (key == XK_Up || key == XK_w || key == XK_W)
		data->y_matrix -= 10;
	else if (key == XK_Down || key == XK_s || key == XK_S)
		data->y_matrix += 10;
	else if (key == XK_Left || key == XK_a || key == XK_A)
		data->x_matrix -= 10;
	else if (key == XK_Right || key == XK_d || key == XK_D)
		data->x_matrix += 10;
	mlx_clear_window(data->mlx, data->mlx_win);
	draw_map(data);
	return ;
}

void	zoom_matrix(int key, t_data *data)
{
	if (key == XK_plus || key == XK_KP_Add)
		data->zoom++;
	else if (key == XK_minus || key == XK_KP_Subtract)
		data->zoom--;
	mlx_clear_window(data->mlx, data->mlx_win);
	draw_map(data);
	return ;
}

void	close_program(t_data *data)
{
	free_matrix(data);
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(EXIT_SUCCESS);
}

void	rotate_matrix(int key, t_data *data)
{
	if (key == XK_Up)
		data->x_rotation += 0.1;
	else if (key == XK_Down)
		data->x_rotation -= 0.1;
	else if (key == XK_Right)
		data->y_rotation += 0.1;
	else if (key == XK_Left)
		data->y_rotation -= 0.1;
	mlx_clear_window(data->mlx, data->mlx_win);
	draw_map(data);
	return ;
}

int	deal_key(int key, t_data *data)
{
	if (key == XK_Escape)
		close_program(data);
	else if (key == XK_w || key == XK_W || key == XK_s || key == XK_S ||
			key == XK_a || key == XK_A || key == XK_d || key == XK_D)
		move_matrix(key, data);
	else if (key == XK_plus || key == XK_KP_Add || key == XK_minus ||
			key == XK_KP_Subtract)
		zoom_matrix(key, data);
	else if (key == XK_Left || key == XK_Right || key == XK_Up ||
			key == XK_Down)
		rotate_matrix(key, data);
	return (key);
}

void	data_init(t_data *data)
{
	get_active_display_size(data);
	data->color = 0;
	data->matrix = NULL;
	data->mlx = NULL;
	data->mlx_win = NULL;
	data->zoom = 30;
	data->x_matrix = (data->display_size_x / 2) - data->width;
	data->y_matrix = (data->display_size_y / 2) - data->height;
	data->x_rotation = 0;
	data->y_rotation = 0;
}

int	main(int argc, char **argv)
{
	t_data	data;

	data_init(&data);
	if (argc != 2)
		return (1) ;
	read_map(argv[1], &data);
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, data.display_size_x,
			data.display_size_y, "Fdf");
	mlx_loop(data.mlx);
	close_program(&data);
}
