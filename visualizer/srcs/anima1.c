/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anima1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 18:48:27 by selly             #+#    #+#             */
/*   Updated: 2020/02/19 18:49:43 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

char			get_chr(char *line)
{
	char		res;

	res = 0;
	while (*line != ' ' && *line)
	{
		line++;
	}
	if (*line == ' ')
		return (*line);
	return (res);
}

int				get_room(t_begin *room, char *place, int flag)
{
	char		*name;
	int			len;
	int			go;

	go = 1;
	if (get_chr(place) == 0)
		len = ft_strlen(place);
	else
		len = ft_strchr(place, ' ') - place;
	while (room->next && go)
	{
		if (room->read == 1)
		{
			name = room->str;
			if (len == ft_strchr(name, ' ') - name
				&& ft_strncmp(name, place, len) == 0)
				go = 0;
		}
		room = room->next;
	}
	return (flag == 1 ? get_xy(name, 1) * 2 + 1 : get_xy(name, 2) * 2 + 1);
}

t_lemings		*get_leming(t_map *map, int ant)
{
	t_lemings	*lem;

	lem = map->lems;
	while (--ant)
	{
		lem = lem->next;
	}
	return (lem);
}

void			new_coords(t_map **map, int ant, char *room)
{
	t_lemings	*lem;

	lem = get_leming(*map, ant);
	if (lem->in_start == 0)
	{
		lem->x_pos = lem->x_go;
		lem->y_pos = lem->y_go;
	}
	if (lem->in_finish != 1)
	{
		lem->x_go = get_room((*map)->read, room, 1);
		lem->y_go = get_room((*map)->read, room, 2);
	}
	if (lem->in_finish == 0 && get_troom((*map)->read, 'x', 2) ==
		lem->x_go && get_troom((*map)->read, 'y', 2) == lem->y_go)
	{
		(*map)->ants_finish += 1;
		lem->in_finish = 1;
	}
	if (lem->in_start == 1 && (get_troom((*map)->read, 'x', 1) !=
		lem->x_go || get_troom((*map)->read, 'y', 1) != lem->y_go))
	{
		(*map)->ants_start -= 1;
		lem->in_start = 0;
	}
}

void			change_position(char *line, t_map **map, t_draw *draw)
{
	int			ant;
	t_lemings	*lems;
	int			x;

	while (*line)
	{
		if (*line == 'L' && *line)
			line++;
		ant = ft_atoi(line);
		while (*line != '-' && *line)
			line++;
		line++;
		new_coords(&(*map), ant, line);
		while (*line != ' ' && *line)
			line++;
		if (*line)
			line++;
	}
	lems = (*map)->lems;
	start_draw(*map, draw, 0, 0);
}
