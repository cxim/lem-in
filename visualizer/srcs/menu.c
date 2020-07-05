/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 19:03:53 by selly             #+#    #+#             */
/*   Updated: 2020/02/19 19:05:33 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

int				control_color(int i, int m)
{
	int			place;

	place = m / 6;
	if (i % m < place)
		return (0x333333);
	else if (i % m < place * 2)
		return (0x006666);
	else if (i % m < place * 3)
		return (0x003333);
	else if (i % m < place * 4)
		return (0x330066);
	else if (i % m < place * 5)
		return (0x003366);
	else
		return (0x000000);
}

char			*ft_itoa_clear(int value)
{
	char		*str;
	char		*tmp;

	tmp = ft_itoa(value);
	str = tmp;
	free(tmp);
	return (str);
}

void			coords(t_draw *draw)
{
	int			x;
	int			y;

	x = 5;
	y = 500;
	mlx_string_put(draw->mlx_ptr, draw->win_ptr, x, y, 0x0000, "x = ");
	mlx_string_put(draw->mlx_ptr, draw->win_ptr,
			x += 40, y, 0x0000, ft_itoa_clear(draw->s_x));
	mlx_string_put(draw->mlx_ptr, draw->win_ptr, x += 50, y, 0x0000, "y = ");
	mlx_string_put(draw->mlx_ptr, draw->win_ptr, x += 40,
			y, 0x0000, ft_itoa_clear(draw->s_y));
	mlx_string_put(draw->mlx_ptr, draw->win_ptr, x = 5,
			450, 0x9A1F6A, "Start: ");
	mlx_string_put(draw->mlx_ptr, draw->win_ptr, 90,
			450, 0x9A1F6A, ft_itoa_clear(draw->s_map->ants_start));
	mlx_string_put(draw->mlx_ptr, draw->win_ptr, 5, 470, 0x9A1F6A, "Finish: ");
	mlx_string_put(draw->mlx_ptr, draw->win_ptr, 90, 470, 0x9A1F6A,
			ft_itoa_clear(draw->s_map->ants_finish));
}

void			put_room_name(t_map *map, t_draw *draw)
{
	t_begin		*s;
	int			i;
	char		**name;

	s = map->read;
	i = 0;
	while (s)
	{
		if (s->read == 1)
		{
			name = ft_strsplit(s->str, ' ');
			put_name(project(new_point(ft_atoi(name[1]) * 2 + 1,
					ft_atoi(name[2]) * 2 + 1, map, 1), draw), draw, name[0]);
			while (name[i])
			{
				free(name[i]);
				i++;
			}
			if (name)
				free(name);
			name = NULL;
		}
		s = s->next;
	}
}

void			text_menu(t_draw *draw)
{
	int			y;
	void		*mlx;
	void		*win;

	y = 0;
	if (draw->flag_move_mouse == 1)
		coords(draw);
	mlx = draw->mlx_ptr;
	win = draw->win_ptr;
	mlx_string_put(mlx, win, 5, y += 10, 0xFF00FF, "Controls");
	mlx_string_put(mlx, win, 5, y += 35, 0x0FF0, "Move:");
	mlx_string_put(mlx, win, 10, y += 20, 0x000000, "- Left Arrow");
	mlx_string_put(mlx, win, 10, y += 20, 0x000000, "- Right Arrow");
	mlx_string_put(mlx, win, 10, y += 20, 0x000000, "- Up Arrow");
	mlx_string_put(mlx, win, 10, y += 20, 0x000000, "- Down Arrow");
	mlx_string_put(mlx, win, 5, y += 35, 0x0FF0, "Rotate:");
	mlx_string_put(mlx, win, 5, y += 20, 0x000000, "for x: -a and -d");
	mlx_string_put(mlx, win, 5, y += 20, 0x000000, "for y: -w and -s");
	mlx_string_put(mlx, win, 5, y += 20, 0x000000, "diagonal: -q and -e");
	mlx_string_put(mlx, win, 10, y += 35, 0x0FF0, "Height control:");
	mlx_string_put(mlx, win, 5, y += 20, 0x000000, "for z: -1 and -2");
	mlx_string_put(mlx, win, 10, y += 35, 0xFF00FF, "Projection:");
	mlx_string_put(mlx, win, 5, y += 20, 0x000000, "-i: isometric");
	mlx_string_put(mlx, win, 5, y += 20, 0x000000, "-p: parallel");
	put_room_name(draw->s_map, draw);
}
