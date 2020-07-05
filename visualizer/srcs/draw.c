/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 18:55:01 by selly             #+#    #+#             */
/*   Updated: 2020/02/19 18:55:03 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

t_point			new_point(int x, int y, t_map *map, int flag)
{
	t_point		point;
	int			index;

	index = y * map->width + x;
	point.x = x;
	point.y = y;
	point.z = map->z_array[index];
	if (flag)
	{
		point.color = (map->color_array[index] == -1) ?
			get_default_color(point.z, map) : map->color_array[index];
	}
	else
		point.color = 0xFFFFFF;
	return (point);
}

void			put_pixel(t_draw *draw, int x, int y, int color)
{
	int			i;

	if (x >= draw->menu && x < draw->w_window && y >= 0 && y < draw->h_window)
	{
		i = (x * draw->bits_per_pixel / 8) + (y * draw->size_line);
		draw->data_addres[i] = color;
		draw->data_addres[++i] = color >> 8;
		draw->data_addres[++i] = color >> 16;
	}
}

void			draw_line(t_point f, t_point s, t_draw *draw)
{
	t_point		delta;
	t_point		sign;
	t_point		cur;
	int			error[2];

	delta.x = (s.x - f.x) < 0 ? -(s.x - f.x) : (s.x - f.x);
	delta.y = (s.y - f.y) < 0 ? -(s.y - f.y) : (s.y - f.y);
	sign.x = f.x < s.x ? 1 : -1;
	sign.y = f.y < s.y ? 1 : -1;
	error[0] = delta.x - delta.y;
	cur = f;
	while (cur.x != s.x || cur.y != s.y)
	{
		put_pixel(draw, cur.x, cur.y, g_color(cur, f, s, delta));
		if ((error[1] = error[0] * 2) > -delta.y)
		{
			error[0] -= delta.y;
			cur.x += sign.x;
		}
		if (error[1] < delta.x)
		{
			error[0] += delta.x;
			cur.y += sign.y;
		}
	}
}

void			fill_background(t_draw *draw)
{
	int			*image;
	int			i;

	ft_bzero(draw->data_addres,
			draw->w_window * draw->h_window * (draw->bits_per_pixel / 8));
	image = (int *)(draw->data_addres);
	i = 0;
	while (i < draw->w_window * draw->h_window)
	{
		image[i] = (i % draw->w_window < draw->menu && i <=
				draw->w_window * 550) ? 0xFFFFFF : draw->s_map->back;
		if (i > draw->w_window * 550 && i <= draw->w_window * 600)
		{
			image[i] = (i % draw->w_window < draw->menu) ?
					control_color(i, draw->menu) : draw->s_map->back;
		}
		i++;
	}
}

void			start_draw(t_map *map, t_draw *draw, int x, int y)
{
	fill_background(draw);
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (x != draw->s_map->width - 1)
				draw_line(project(new_point(x, y, map, 1), draw),
						project(new_point(x + 1, y, map, 1), draw), draw);
			if (y != draw->s_map->height - 1)
				draw_line(project(new_point(x, y, map, 1), draw),
						project(new_point(x, y + 1, map, 1), draw), draw);
			x++;
		}
		y++;
	}
	put_links(map, draw);
	put_lems(map, draw, map->ants);
	draw->null_camera = draw->i == 0 ? c_cam(draw) : draw->null_camera;
	mlx_put_image_to_window(draw->mlx_ptr, draw->win_ptr, draw->img_ptr, 0, 0);
	text_menu(draw);
}
