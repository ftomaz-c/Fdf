/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:54:03 by ftomaz-c          #+#    #+#             */
/*   Updated: 2023/12/14 23:14:12 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <math.h>

void rotate_y(float *x, float *z, t_data *data)
{
	float temp_x;

	temp_x = *x;
	*x = *x * cos(data->y_rotation) + *z * sin(data->y_rotation);
	*z = -temp_x * sin(data->y_rotation) + *z * cos(data->y_rotation);
}

void rotate_x(float *y, float *z, t_data *data)
{
	float temp_y;

	temp_y = *y;
	*y = *y * cos(data->x_rotation) - *z * sin(data->x_rotation);
	*z = temp_y * sin(data->x_rotation) + *z * cos(data->x_rotation);
}

void	isometric(float *x, float *y, float z, t_data *data)
{
	*x = (*x - *y) * cos(0.8);
	*y = (*x + *y) * sin(0.8) - z;

	rotate_y(x, &z, data);
	rotate_x(y, &z, data);
}

float	mod(float x)
{
	if (x < 0)
		x = -x;
	return(x);
}

float	bigger(float x, float y)
{
	if (x > y)
		return (x);
	return (y);
}

void	draw_line(float x, float y, float x1, float y1, t_data *data)
{
	float	x_step;
	float	y_step;
	int		max;
	int		z;
	int		z1;


	z = data->matrix[(int)y][(int)x];
	z1 = data->matrix[(int)y1][(int)x1];

	//---------zoom----------
	x *= data->zoom;
	y *= data->zoom;
	x1 *= data->zoom;
	y1 *= data->zoom;
	//---------color----------
	if (z || z1)
		data->color =  0xFF0000;
	else
		data->color = 0xFFFFFF;

	//----------3D----------
	isometric(&x, &y, z, data);
	isometric(&x1, &y1, z1, data);

	x += data->x_matrix;
	y += data->y_matrix;
	x1 += data->x_matrix;
	y1 += data->y_matrix;

	x_step = x1 - x;
	y_step = y1 - y;

	max = bigger(mod(x_step), mod(y_step));

	x_step /= max;
	y_step /= max;

	while ((int)(x - x1) || (int)(y - y1))
	{
		mlx_pixel_put(data->mlx, data->mlx_win, x, y, data->color);
		x += x_step;
		y += y_step;
	}
	return ;
}

void	draw_map(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			if (x < data->width - 1)
				draw_line(x, y, x + 1, y, data);
			if (y < data->height - 1)
				draw_line(x, y, x, y + 1, data);
			x++;
		}
		y++;
	}
}
