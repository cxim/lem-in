/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diekctra2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:14:36 by selly             #+#    #+#             */
/*   Updated: 2020/02/19 17:19:23 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

char		**new_tab(int size)
{
	char	**res;
	int		i;

	i = 0;
	res = (char **)malloc(sizeof(char *) * (size + 500));
	while (i < (size + 499))
		res[i++] = NULL;
	return (res);
}

t_room		*new_ptr_dieks(t_room *head, t_room *tmp)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	tmp->dieks.done = 1;
	while (head[++i].name)
	{
		if (!(head[i].dieks.done) && ((j > head[i].dieks.len
			&& head[i].dieks.len > 0) || !(j)))
			j = head[i].dieks.len;
	}
	i = -1;
	while ((j > 0) && head[++i].name)
		if ((head[i].dieks.len == j && !(head[i].dieks.done)))
			return (head + i);
	return (NULL);
}

t_way		get_dieks(t_room *end)
{
	t_way	res;
	int		i;

	i = end->dieks.len;
	res.len = end->dieks.len;
	res.road = new_sizet_tab(i);
	res.road[i--] = (size_t)end;
	while (!(end->start))
	{
		res.road[i--] = end->dieks.room;
		end = (t_room *)(end->dieks.room);
	}
	return (res);
}

t_way		empty_way(void)
{
	t_way	ret;

	ret.road = NULL;
	ret.len = -1;
	ret.ants = -1;
	ret.value = -1;
	return (ret);
}

t_way		best_way(t_room *head)
{
	t_room	*tmp1;
	t_room	*tmp2;
	t_room	*end;
	int		i;

	end = find_end(head);
	tmp1 = find_start(head);
	while (tmp1 && !(end->dieks.room))
	{
		i = -1;
		while ((tmp2 = (t_room *)(tmp1->link[++i])))
			if (((tmp2->dieks.len) > (tmp1->dieks.len + 1) ||
				!(tmp2->dieks.len)) && !(tmp2->dieks.done))
			{
				tmp2->dieks.room = (size_t)(tmp1);
				tmp2->dieks.len = (tmp1->dieks.len + 1);
			}
		tmp1 = new_ptr_dieks(head, tmp1);
	}
	if (end->dieks.room)
		return (get_dieks(end));
	return (empty_way());
}
