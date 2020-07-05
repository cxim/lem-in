/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_settings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 19:05:40 by selly             #+#    #+#             */
/*   Updated: 2020/02/19 19:05:50 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

void		change_back(t_draw *draw)
{
	int		place;

	place = draw->menu / 6;
	if (draw->s_x <= place)
		draw->s_map->back = 0x333333;
	else if (draw->s_x < place * 2)
		draw->s_map->back = 0x006666;
	else if (draw->s_x < place * 3)
		draw->s_map->back = 0x003333;
	else if (draw->s_x < place * 4)
		draw->s_map->back = 0x330066;
	else if (draw->s_x < place * 5)
		draw->s_map->back = 0x003366;
	else
		draw->s_map->back = 0x000000;
	start_draw(draw->s_map, draw, 0, 0);
}

int			mouse_press(int button, int x, int y, t_draw *draw)
{
	if (button == 4)
		zoom(draw, 0);
	else if (button == 5)
		zoom(draw, 1);
	else if (button == 1)
	{
		draw->mouse->but_pressed = 1;
		if (y >= 550 && y <= 600 && x <= draw->menu)
			change_back(draw);
	}
	return (x + y);
}

int			mouse_release(int button, int x, int y, t_draw *draw)
{
	if (button == 1)
		draw->mouse->but_pressed = 0;
	return (x + y);
}

double		s(t_draw *draw)
{
	int		x;

	x = draw->speed;
	if (x == 0)
		return (0.01);
	else if (x == 1)
		return (0.002);
	else if (x == 2)
		return (0.007);
	else if (x > 2 || x < 0)
		return (0.01);
	else
		return (0);
}

int			mouse_move(int x, int y, t_draw *draw)
{
	draw->flag_move_mouse = 1;
	start_draw(draw->s_map, draw, 0, 0);
	draw->s_x = x;
	draw->s_y = y;
	draw->mouse->x = draw->mouse->next_x;
	draw->mouse->y = draw->mouse->next_y;
	draw->mouse->next_x = x;
	draw->mouse->next_y = y;
	if (draw->mouse->but_pressed && draw->flag_iso_par == 1)
	{
		draw->camera->beta += (draw->mouse->next_x - draw->mouse->x) * s(draw);
		draw->camera->alpha += (draw->mouse->next_y - draw->mouse->y) * s(draw);
		start_draw(draw->s_map, draw, 0, 0);
	}
	else if (draw->mouse->but_pressed && draw->flag_iso_par == 2)
	{
		draw->camera->beta += (((double)(draw->mouse->next_x
				- draw->mouse->x) / 2) * s(draw));
		draw->camera->alpha += (((double)(draw->mouse->next_y
				- draw->mouse->y) / 2) * s(draw));
		start_draw(draw->s_map, draw, 0, 0);
	}
	return (0);
}
