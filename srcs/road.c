/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   road.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 18:07:04 by selly             #+#    #+#             */
/*   Updated: 2020/02/19 18:07:27 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		new_way_group(t_way **tmp1, t_way *tmp2, t_way *tmp3)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	(*tmp1) = new_roads(find_nbr_roads(tmp2));
	while (tmp3[++i].road)
	{
		if (!(i))
			(*tmp1)[++j] = tmp2[0];
		if (!(have_connect((*tmp1), tmp3[i])))
			(*tmp1)[++j] = tmp3[i];
	}
}

void		init_roads(t_way *head, int n_ants)
{
	int		i;

	i = -1;
	while (head[++i].road)
	{
		if (!(i))
			head[i].ants = n_ants;
		else
			head[i].ants = 0;
		head[i].value = (head[i].len + head[i].ants - 1);
	}
}

int			count_turn_solve(t_way *head, int n_ants)
{
	int		res;
	int		i;

	i = -1;
	init_roads(head, n_ants);
	res = head[0].value;
	while (head[(++i + 1)].road)
	{
		if (head[i].value > head[(i + 1)].value)
		{
			while (head[i].value > head[(i + 1)].value)
			{
				head[i].value--;
				head[(i + 1)].value++;
				head[i].ants--;
				head[(i + 1)].ants++;
			}
			res = head[(i + 1)].value;
			i = -1;
		}
	}
	return (res);
}

t_way		*best_way_group(t_way *head, int n_ants)
{
	t_way	*res;
	t_way	*tmp;
	int		i;
	int		j;

	i = -1;
	tmp = NULL;
	res = NULL;
	new_way_group(&res, head, head);
	while (head[++i].road)
	{
		j = i;
		while (head[++j].road)
		{
			new_way_group(&tmp, (head + i), (head + j));
			if ((count_turn_solve(tmp, n_ants)) <
				(count_turn_solve(res, n_ants)))
			{
				free(res);
				new_way_group(&res, (head + i), (head + j));
			}
			free(tmp);
		}
	}
	return (res);
}

int			stay_on(t_way *head)
{
	int		i;

	i = -1;
	while (head[++i].road)
		if (head[i].value != 0)
			return (1);
	return (0);
}
