/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 18:55:14 by selly             #+#    #+#             */
/*   Updated: 2020/02/19 18:58:24 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

void			put_links(t_map *map, t_draw *draw)
{
	t_begin		*s;

	s = map->read;
	while (s)
	{
		if (s->read == 2)
		{
			draw_line(project(new_point(from(s->str, map->read, 1, 1),
					from(s->str, map->read, 0, 1), map, 1), draw),
					project(new_point(to(s->str, map->read, 1),
					to(s->str, map->read, 0), map, 1), draw), draw);
		}
		s = s->next;
	}
}

int				from(char *links, t_begin *room, int flag, int go)
{
	char		*buf;
	char		*name;
	int			i;

	buf = links;
	while (room->next && go)
	{
		if (room->read == 1)
		{
			name = room->str;
			i = 0;
			while (name[i] == *links && *links != '-')
			{
				i++;
				links++;
			}
			if (*links == '-' && name[i] == ' ')
				go = 0;
			else
				links = buf;
		}
		room = room->next;
	}
	return (flag == 1 ? get_xy(name, 1) * 2 + 1 : get_xy(name, 2) * 2 + 1);
}

int				to(char *links, t_begin *room, int flag)
{
	char		*name;
	int			go;
	int			len;

	while (*links != '-' && *links)
		links++;
	links++;
	go = 1;
	len = ft_strlen(links);
	name = NULL;
	while (room->next && go)
	{
		if (room->read == 1)
		{
			name = room->str;
			if (len == ft_strchr(name, ' ') - name &&
				ft_strncmp(name, links, len) == 0)
				go = 0;
		}
		room = room->next;
	}
	return (flag == 1 ? get_xy(name, 1) * 2 + 1 : get_xy(name, 2) * 2 + 1);
}

void			put_lems(t_map *map, t_draw *draw, int ants)
{
	t_lemings	*lems;
	int			color;

	lems = map->lems;
	color = 0xFFFFFF;
	while (lems->next)
	{
		if (lems->in_start == 1)
		{
			put_lem(project(new_point(lems->x_pos, lems->y_pos, map, 0),
					draw), project(new_point(lems->x_go,
					lems->y_go, map, 0), draw), draw, color);
		}
		else
		{
			put_lem(project(new_point(lems->x_go, lems->y_go, map, 0), draw),
					project(new_point(lems->x_pos, lems->y_pos, map, 0),
					draw), draw, color);
		}
		map->go = 0;
		lems = lems->next;
	}
}
