/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 19:06:05 by selly             #+#    #+#             */
/*   Updated: 2020/02/19 19:06:23 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

static void		rotate_x(int *y, int *z, double alpha)
{
	int			previous_y;

	previous_y = *y;
	*y = previous_y * cos(alpha) + *z * sin(alpha);
	*z = -previous_y * sin(alpha) + *z * cos(alpha);
}

static void		rotate_y(int *x, int *z, double beta)
{
	int			previous_x;

	previous_x = *x;
	*x = previous_x * cos(beta) + *z * sin(beta);
	*z = -previous_x * sin(beta) + *z * cos(beta);
}

static void		rotate_z(int *x, int *y, double gamma)
{
	int			previous_x;
	int			previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = previous_x * cos(gamma) - previous_y * sin(gamma);
	*y = previous_x * sin(gamma) + previous_y * cos(gamma);
}

static void		iso(int *x, int *y, int z)
{
	int			previous_x;
	int			previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = (previous_x - previous_y) * cos(0.523599);
	*y = -z + (previous_x + previous_y) * sin(0.523599);
}

t_point			project(t_point p, t_draw *draw)
{
	p.x *= draw->camera->zoom;
	p.y *= draw->camera->zoom;
	p.z *= draw->camera->zoom / draw->camera->z_divisor;
	p.x -= (draw->s_map->width * draw->camera->zoom) / 2;
	p.y -= (draw->s_map->height * draw->camera->zoom) / 2;
	rotate_x(&p.y, &p.z, draw->camera->alpha);
	rotate_y(&p.x, &p.z, draw->camera->beta);
	rotate_z(&p.x, &p.y, draw->camera->gamma);
	if (draw->camera->projection == ISOMETRIC)
		iso(&p.x, &p.y, p.z);
	p.x += (draw->w_window - draw->menu) / 2 + draw->camera->x_offset
		+ draw->menu;
	p.y += (draw->h_window + draw->s_map->height * draw->camera->zoom) / 3
		+ draw->camera->y_offset;
	return (p);
}
