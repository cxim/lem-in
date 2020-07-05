/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_structure_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 18:59:07 by selly             #+#    #+#             */
/*   Updated: 2020/02/19 18:59:43 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

void			put_name(t_point a, t_draw *draw, char *name)
{
	mlx_string_put(draw->mlx_ptr, draw->win_ptr, a.x + 5, a.y, 0xFFFF00, name);
}

int				get_h(char *screen)
{
	char		*h;

	while (*screen != 'x')
		screen++;
	screen++;
	h = screen;
	return (ft_atoi(h));
}

int				*get_windows_size(char *screen, t_draw **draw, int w, int h)
{
	if (screen)
	{
		w = ft_atoi(screen);
		h = get_h(screen);
		if (w >= 800 && h >= 600 && w < 2100 && h < 4100)
		{
			(*draw)->w_window = w;
			(*draw)->h_window = h;
			(*draw)->menu = w / 4;
			return (0);
		}
		else
		{
			(*draw)->w_window = 800;
			(*draw)->h_window = 600;
			(*draw)->menu = 200;
			return (0);
		}
	}
	(*draw)->w_window = 1440;
	(*draw)->h_window = 900;
	(*draw)->menu = 492;
	return (0);
}

t_draw			*new_draw(t_map *map, char *screen, t_mouse *mouse, char *speed)
{
	t_draw		*draw;

	if (!(draw = (t_draw *)ft_memalloc(sizeof(t_draw))))
		print_error("Malloc error.");
	if (!(draw->mlx_ptr = mlx_init()))
		print_error("MLX can not initiate.");
	get_windows_size(screen, &draw, 0, 0);
	draw->speed = ft_atoi(speed);
	if (!(draw->win_ptr = mlx_new_window(draw->mlx_ptr,
					draw->w_window, draw->h_window, "FdF")))
		print_error("New window can not initiate.");
	if (!(draw->img_ptr = mlx_new_image(draw->mlx_ptr,
					draw->w_window, draw->h_window)))
		print_error("New image can not initiate.");
	draw->mouse = mouse;
	draw->i = 0;
	draw->data_addres = mlx_get_data_addr(draw->img_ptr,
			&(draw->bits_per_pixel), &(draw->size_line), &(draw->endian));
	draw->s_map = map;
	return (draw);
}

t_map			*new_map(t_begin *n, int max_x, int max_y, int ants)
{
	t_map		*map;

	if (!(map = (t_map *)ft_memalloc(sizeof(t_map))))
		print_error("Malloc error.");
	map->height = max_y;
	map->len = max_x * max_y;
	map->go = 0;
	map->z_max = 50;
	map->z_min = 0;
	map->max_move = get_moves(n);
	map->move = 0;
	map->width = max_x;
	map->lems = new_lems(n, ants, get_troom(n, 'x', 1));
	map->back = 0x000000;
	map->frame = 0;
	map->ants = ants;
	map->ants_start = ants;
	map->ants_finish = 0;
	map->read = n;
	map->z_array = 0;
	map->color_array = 0;
	return (map);
}
