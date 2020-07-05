/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 18:50:57 by selly             #+#    #+#             */
/*   Updated: 2020/02/19 18:53:56 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

void			test_rooms(t_begin *new)
{
	int			rooms;
	t_begin		*head;

	rooms = 0;
	head = new;
	while (new->next)
	{
		if (new->read == 1)
			rooms++;
		new = new->next;
	}
	if (rooms > 100)
	{
		free_begin(&head);
		print_error("Sorry the map is too big!\n");
	}
}

int				get_xy(char *s, int flag)
{
	int			result;

	result = 0;
	while (*s != ' ')
	{
		s++;
	}
	if (flag == 1)
		result = ft_atoi(s);
	if (flag == 2)
	{
		while (*s == ' ')
		{
			s++;
		}
		while (*s != ' ')
		{
			s++;
		}
		result = ft_atoi(s);
	}
	return (result);
}

int				test_xy(t_begin *new, int flag)
{
	t_begin		*head;
	int			max;
	int			val;

	head = new;
	max = -214;
	while (new->next)
	{
		if (new->type)
		{
			val = get_xy(new->str, flag);
			if (max < val)
				max = val;
		}
		new = new->next;
	}
	if (max > 100 || max < 0)
	{
		free_begin(&head);
		print_error("Sorry the map is too big!\n");
	}
	return (max);
}

int				type_of_room(char *line)
{
	int			type;

	type = 3;
	if (ft_strcmp(line, "##start") == 0)
		type = 1;
	else if (ft_strcmp(line, "##end") == 0)
		type = 2;
	return (type);
}

void			parser_lemin(t_begin *new, int ants)
{
	int			max_x;
	int			max_y;
	t_map		*map;

	if (!(new->next))
	{
		free_begin(&new);
		print_error("Map error.");
	}
	test_rooms(new);
	max_x = test_xy(new, 1) * 2 + 3;
	max_y = test_xy(new, 2) * 2 + 3;
	map = new_map(new, max_x, max_y, ants);
	start_visual(map, "1400x800", "3");
}
