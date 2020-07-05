/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_some.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:26:59 by selly             #+#    #+#             */
/*   Updated: 2020/02/19 17:27:38 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_room		*find_end(t_room *head)
{
	t_room	*res;

	res = head;
	while (res->name && !(res->end))
		res++;
	return (res);
}

t_room		*find_start(t_room *head)
{
	t_room	*res;

	res = head;
	while (res->name && !(res->start))
		res++;
	return (res);
}

int			find_num_ants(t_room *head)
{
	t_room	*tmp;

	tmp = head;
	while (!(tmp->start))
		tmp++;
	return (tmp->num_ants);
}

int			find_num_ways(t_room *head)
{
	int		res;
	t_room	*tmp;

	res = 0;
	tmp = find_end(head);
	while (tmp->link[res])
		res++;
	return ((res * 2));
}

int			find_nbr_roads(t_way *head)
{
	int		res;

	res = 0;
	while (head[res].road)
		res++;
	return (res);
}
