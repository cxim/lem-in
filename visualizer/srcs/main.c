/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 19:02:02 by selly             #+#    #+#             */
/*   Updated: 2020/02/19 19:02:39 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

int				get_coord(char *read, int max_x)
{
	int			x;
	int			y;

	x = get_xy(read, 1) * 2 + 1;
	y = get_xy(read, 2) * 2 + 1;
	return (max_x * y + x);
}

void			arr_of_values(t_map *map, t_begin *read)
{
	int			i;

	i = 0;
	if ((!(map->color_array = (int *)malloc(sizeof(int) * map->len))) ||
	(!(map->z_array = (int *)malloc(sizeof(int) * map->len))))
		print_error("Malloc error\n");
	while (i < map->len)
	{
		map->z_array[i] = 0;
		map->color_array[i] = -1;
		i++;
	}
	while (read->next)
	{
		if (read->read == 1)
			map->z_array[get_coord(read->str,
					map->width)] = read->type == 3 ? 50 : 25;
		read = read->next;
	}
}

void			start_visual(t_map *map, char *screen, char *speed)
{
	t_draw		*draw;
	t_mouse		*mouse;

	mouse = new_mouse();
	draw = new_draw(map, screen, mouse, speed);
	arr_of_values(map, map->read);
	draw->camera = new_camera(draw, map);
	draw->flag_iso_par = 2;
	start_draw(draw->s_map, draw, 0, 0);
	mlx_hook(draw->win_ptr, 2, 0, key_press, draw);
	mlx_hook(draw->win_ptr, 4, 0, mouse_press, draw);
	mlx_hook(draw->win_ptr, 5, 0, mouse_release, draw);
	mlx_hook(draw->win_ptr, 6, 0, mouse_move, draw);
	mlx_hook(draw->win_ptr, 17, 0, close_win, &draw);
	mlx_loop(draw->mlx_ptr);
}

void			start_read(t_begin *new, int ants, int s_e, char *line)
{
	t_begin		*head;

	head = new;
	while (get_next_line(0, &line) > 0)
	{
		if (line[0] != '#' && line[0] != 0)
		{
			if (s_e == 0)
				ants = ft_atoi(line);
			else if (ft_strlen(line) > 0)
			{
				new = full_rooms_coord(line, new, &s_e);
				new->next = new_begin();
				new = new->next;
			}
			else if (ft_strlen(line) == 0)
				free_memory(&line, &head);
		}
		s_e = type_of_room(line);
		free(line);
		line = NULL;
	}
	parser_lemin(head, ants);
	free_memory(&line, &head);
}

int				main(void)
{
	t_begin		*new;
	int			ants;
	char		*line;

	line = NULL;
	new = new_begin();
	ants = 0;
	start_read(new, ants, 0, line);
	free(&new);
	return (0);
}
