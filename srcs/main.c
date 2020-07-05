/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:29:17 by selly             #+#    #+#             */
/*   Updated: 2020/02/19 17:29:50 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int			check_way(t_room *head, int flag)
{
	t_room	*start;
	t_room	*end;
	t_way	way;

	end = find_end(head);
	start = find_start(head);
	if (!(end->link) || !(start->link))
		return (1);
	way = best_way(head);
	if (way.len == -1 && flag == 1)
		exit(-10);
	if (way.road)
		free(way.road);
	return (0);
}

int			check_one_step_way(t_room *head)
{
	t_room	*tmp1;
	t_room	*tmp2;
	int		i;

	i = -1;
	tmp1 = find_start(head);
	while (tmp1->name && tmp1->link[++i])
	{
		tmp2 = ((t_room *)(tmp1->link[i]));
		if (tmp2->end)
			return (1);
	}
	return (0);
}

void		start_lem(int fd, t_room **head, char **map)
{
	t_way	*w_group;
	t_way	*roads;

	i_prms(&(*head), &w_group, &roads, &map);
	if ((map = pars_map(&(*head), fd, 0, -1)) && (*head))
	{
		if (check_way((*head), 1))
		{
			map = free_map(map);
			free_all(&(*head), &roads, &w_group);
			ft_printf("{red}ERROR{eoc}\n");
			return ;
		}
		map = print_map(map);
		if (check_one_step_way(*head))
			print_one_way(*head, find_num_ants(*head));
		else
		{
			roads = find_ways_di(*head);
			w_group = best_way_group(roads, find_num_ants(*head));
			count_turn_solve(w_group, (find_num_ants(*head)));
			print_way_group(w_group, (find_num_ants(*head)));
		}
	}
	free_all(&(*head), &roads, &w_group);
}

void		start_read(char *str)
{
	int		fd;
	t_room	*head;
	char	**map;

	map = NULL;
	head = NULL;
	if (str == NULL)
		fd = 0;
	else if ((fd = open(str, O_RDONLY)) < 0)
	{
		ft_printf("{red}Can not open the map {eoc}\n");
		exit(0);
	}
	start_lem(fd, &head, map);
	close(fd);
}

int			main(int argv, char **argc)
{
	if (argv == 2)
		start_read(argc[1]);
	if (argv == 1)
		start_read(NULL);
	return (0);
}
