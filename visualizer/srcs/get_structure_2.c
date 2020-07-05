/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_structure_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 18:59:47 by selly             #+#    #+#             */
/*   Updated: 2020/02/19 19:00:03 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

t_camera		*c_cam(t_draw *draw)
{
	t_camera	*camera;

	if (!(camera = (t_camera *)malloc(sizeof(t_camera))))
		print_error("Malloc error.");
	camera->zoom = draw->camera->zoom;
	camera->alpha = draw->camera->alpha;
	camera->beta = draw->camera->beta;
	camera->gamma = draw->camera->gamma;
	camera->z_divisor = draw->camera->z_divisor;
	camera->x_offset = draw->camera->x_offset;
	camera->y_offset = draw->camera->y_offset;
	draw->i = 1;
	return (camera);
}

int				minimum(int a, int b)
{
	return (a < b ? a : b);
}

t_mouse			*new_mouse(void)
{
	t_mouse		*mouse;

	if (!(mouse = (t_mouse *)ft_memalloc(sizeof(t_mouse))))
		print_error("Malloc error.");
	mouse->x = 0;
	mouse->y = 0;
	mouse->next_x = 0;
	mouse->next_y = 0;
	mouse->but_pressed = 0;
	return (mouse);
}

t_camera		*new_camera(t_draw *draw, t_map *map)
{
	t_camera	*camera;
	int			devision;

	devision = 3;
	if (!(camera = (t_camera *)ft_memalloc(sizeof(t_camera))))
		print_error("Malloc error.");
	if (abs(map->z_max - map->z_min) > map->height)
		devision = 10;
	camera->zoom = minimum((draw->w_window - draw->menu) / draw->s_map->width
			/ 2, draw->h_window / draw->s_map->height / 2);
	camera->alpha = 0;
	camera->beta = 0;
	camera->gamma = 0;
	camera->z_divisor = devision;
	camera->x_offset = 0;
	camera->y_offset = 0;
	return (camera);
}
