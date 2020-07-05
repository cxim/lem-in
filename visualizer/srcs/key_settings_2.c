/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_settings_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 19:01:31 by selly             #+#    #+#             */
/*   Updated: 2020/02/19 19:01:51 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

int			zoom(t_draw *draw, int zoom)
{
	if (zoom == 0)
		draw->camera->zoom++;
	else if (zoom == 1)
		draw->camera->zoom--;
	if (draw->camera->zoom < 1)
		draw->camera->zoom = 1;
	start_draw(draw->s_map, draw, 0, 0);
	return (0);
}

int			close_win(t_draw **draw)
{
	free((*draw)->camera);
	free((*draw)->mouse);
	free((*draw)->s_map);
	free((*draw)->draw);
	(*draw)->camera = NULL;
	(*draw)->mouse = NULL;
	(*draw)->s_map = NULL;
	(*draw)->draw = NULL;
	free(*draw);
	(*draw) = NULL;
	exit(0);
}

int			iso_par(t_draw *draw, int p)
{
	draw->camera->zoom = draw->null_camera->zoom;
	draw->camera->alpha = draw->null_camera->alpha;
	draw->camera->beta = draw->null_camera->beta;
	draw->camera->gamma = draw->null_camera->gamma;
	draw->camera->z_divisor = draw->null_camera->z_divisor;
	draw->camera->x_offset = draw->null_camera->x_offset;
	draw->camera->y_offset = draw->null_camera->y_offset;
	if (p == 1)
	{
		draw->camera->projection = PARALLEL;
		draw->flag_iso_par = 1;
	}
	else
	{
		draw->camera->projection = ISOMETRIC;
		draw->flag_iso_par = 2;
	}
	start_draw(draw->s_map, draw, 0, 0);
	return (0);
}
