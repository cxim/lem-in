/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_settings_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 19:01:11 by selly             #+#    #+#             */
/*   Updated: 2020/02/19 19:01:27 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

int			z_go(t_draw *draw, int up_down)
{
	if (up_down)
		draw->camera->z_divisor -= 0.2;
	else
		draw->camera->z_divisor += 0.2;
	if (draw->camera->z_divisor < 0.1)
		draw->camera->z_divisor = 0.1;
	else if (draw->camera->z_divisor > 10)
		draw->camera->z_divisor = 10;
	start_draw(draw->s_map, draw, 0, 0);
	return (0);
}

int			move(t_draw *draw, int side)
{
	if (side == 0)
		draw->camera->x_offset -= 10;
	else if (side == 1)
		draw->camera->x_offset += 10;
	else if (side == 2)
		draw->camera->y_offset -= 10;
	else if (side == 3)
		draw->camera->y_offset += 10;
	start_draw(draw->s_map, draw, 0, 0);
	return (0);
}

int			rotate_map(t_draw *draw, int side)
{
	if (side == 0)
		draw->camera->alpha += 0.05;
	else if (side == 1)
		draw->camera->alpha -= 0.05;
	else if (side == 2)
		draw->camera->beta -= 0.05;
	else if (side == 3)
		draw->camera->beta += 0.05;
	else if (side == 4)
		draw->camera->gamma -= 0.05;
	else if (side == 5)
		draw->camera->gamma += 0.05;
	start_draw(draw->s_map, draw, 0, 0);
	return (0);
}

int			key_press_2(int key, t_draw *draw)
{
	if (key == 13)
		rotate_map(draw, 2);
	else if (key == 1)
		rotate_map(draw, 3);
	else if (key == 12)
		rotate_map(draw, 4);
	else if (key == 14)
		rotate_map(draw, 5);
	else if (key == 20)
		zoom(draw, 0);
	else if (key == 49)
	{
		if (draw->s_map->ants != draw->s_map->ants_finish)
			lem_go(draw->s_map->read, &(draw->s_map), draw);
	}
	else if (key == 21)
		zoom(draw, 1);
	else if (key == 53)
		close_win(&draw);
	else
	{
		ft_putstr("key = ");
		ft_putnbr(key);
	}
	return (0);
}

int			key_press(int key, t_draw *draw)
{
	if (key == 18)
		z_go(draw, 1);
	else if (key == 34)
		iso_par(draw, 0);
	else if (key == 35)
		iso_par(draw, 1);
	else if (key == 19)
		z_go(draw, 0);
	else if (key == 123)
		move(draw, 0);
	else if (key == 124)
		move(draw, 1);
	else if (key == 126)
		move(draw, 2);
	else if (key == 125)
		move(draw, 3);
	else if (key == 0)
		rotate_map(draw, 0);
	else if (key == 2)
		rotate_map(draw, 1);
	else
		key_press_2(key, draw);
	return (0);
}
