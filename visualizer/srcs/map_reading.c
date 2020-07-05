/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 19:02:46 by selly             #+#    #+#             */
/*   Updated: 2020/02/19 19:03:42 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

int				get_moves(t_begin *read)
{
	int			lines;

	lines = 0;
	while (read)
	{
		if (read->read == 3)
			lines++;
		read = read->next;
	}
	return (lines);
}

int				get_troom(t_begin *read, char coord, int type)
{
	char		*name;
	int			go;

	name = NULL;
	go = 1;
	while (read->next && go)
	{
		if (read->type == type)
		{
			name = read->str;
			go = 0;
		}
		if (go)
			read = read->next;
	}
	return (coord == 'x' ? get_xy(name, 1) * 2 + 1 : get_xy(name, 2) * 2 + 1);
}

t_lemings		*new_lems(t_begin *new, int ants, int x)
{
	t_lemings	*head;
	t_lemings	*lem;
	int			y;

	if (ants <= 0)
		print_error("Thare are not ants!");
	if (!(lem = (t_lemings *)ft_memalloc(sizeof(t_lemings))))
		print_error("Malloc error.");
	head = lem;
	y = get_troom(new, 'y', 1);
	while (ants)
	{
		lem->x_pos = x;
		lem->y_pos = y;
		lem->x_go = x;
		lem->y_go = y + 5;
		lem->in_start = 1;
		lem->in_finish = 0;
		if (!(lem->next = (t_lemings *)ft_memalloc(sizeof(t_lemings))))
			print_error("Malloc error.");
		lem = lem->next;
		ants--;
	}
	return (head);
}
