/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diekctra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:12:18 by selly             #+#    #+#             */
/*   Updated: 2020/02/19 17:13:07 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		i_prms(t_room **s1, t_way **s2, t_way **s3, char ***s4)
{
	*(s1) = NULL;
	*(s2) = NULL;
	*(s3) = NULL;
	*(s4) = NULL;
}

void		reset_dieks(t_room *head)
{
	int		i;

	i = -1;
	while (head[++i].name)
	{
		head[i].dieks.len = 0;
		head[i].dieks.room = 0;
		head[i].dieks.done = 0;
	}
}

void		block_road(t_way *ways, int *cur_p)
{
	int		i1;
	int		i2;
	int		i3;
	int		i4;
	int		i5;

	i1 = -1;
	while (ways[++i1].road && !(i2 = 0))
	{
		while (ways[i1].road[(++i2 + 1)] && ((i3 = i1) >= 0))
		{
			while (ways[++i3].road && !(i4 = 0))
			{
				while (ways[i3].road[(++i4 + 1)])
					if (ways[i1].road[i2] == ways[i3].road[i4])
						((t_room *)(ways[i1].road[i2]))->dieks.done = 1;
			}
		}
	}
	if ((ways[(*cur_p)].road))
	{
		i5 = (ways[(*cur_p)].len - 1);
		((t_room *)(ways[(*cur_p)++].road[i5]))->dieks.done = 1;
	}
}

void		sort_ways_l_s(t_way *ways)
{
	t_way	tmp;
	int		i;
	int		j;

	j = -1;
	while (ways[++j].road)
	{
		i = j + 1;
		tmp = ways[j];
		while (--i > 0 && ways[i - 1].len > tmp.len)
			ways[i] = ways[i - 1];
		ways[i] = tmp;
	}
}

t_way		*find_ways_di(t_room *head)
{
	t_way	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = new_roads(find_num_ways(head));
	while (1)
	{
		res[i] = best_way(head);
		if (!(res[i].road))
			if (++j > 1)
				break ;
		reset_dieks(head);
		block_road(res, &(i));
	}
	sort_ways_l_s(res);
	if (!(res->road))
		ft_memdel((void **)&res);
	return (res);
}
