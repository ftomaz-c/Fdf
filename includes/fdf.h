/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc < ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 20:20:44 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/30 15:27:00 by ftomazc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// **  ------------------------------- resources --------------------------------
// **	--------------- 3D ------------------------------------------
// **		x` = (x - y) * cos(angle);
// **		y` = (x + y) * sin(angle) - z;
// **	-------------------------------------------------------------
// ** 	------- mlx_function ----------------------------------------
// **		void *mlx_ptr;
// **		void *win_prt;
// **
// **		mlx_ptr = mlx_init();
// **		win_prt = mlx_new_window(mlx_ptr, 1000, 1000, "FDF");
// **
// **		mlx_pixel_put(mlx_ptr, win_ptr, (int)x, (int)y, #color);
// **
// **		mlx_key_hook(win_ptr, deal_key, NULL);
// **		mlx_loop(mlx_ptr);
// **	--------------------------------------------------------------
// **	------- deal_key prototype -----------------------------------
// **		int		deal_key(int key, void *data);
// **	--------------------------------------------------------------
// **	colors:
// **		white = 0xffffff
// **		red = 0xe80c0c
// **	----------------------------
// **	frameworks:
// **		-framework OpenGL -framework AppKit

#ifndef FDF_H
# define FDF_H

# include "../src/mlx_linux/mlx.h"
# include "../src/libft/includes/libft.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include <X11/Xlib.h>
# include <math.h>
# include <fcntl.h>

typedef struct s_data
{
	int		display_size_x;
	int		display_size_y;
	int		width;
	int		height;
	int		**matrix;
	int		zoom;
	int		color;
	float	x_matrix;
	float	y_matrix;
	float	x_rotation;
	float	y_rotation;

	void	*mlx;
	void	*mlx_win;
}				t_data;

void	read_map(char *file_name, t_data *data);
void	draw_line(float x, float y, float x1, float y1, t_data *data);
void	draw_map(t_data *data);

#endif
