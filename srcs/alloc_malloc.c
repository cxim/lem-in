/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:07:43 by selly             #+#    #+#             */
/*   Updated: 2020/02/19 17:07:50 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

char	**realloc_map(char **map, int size)
{
	char	**ret;
	int		i;

	i = -1;
	ret = new_tab(size + 2000);
	if (map)
	{
		while (map[++i])
		{
			ret[i] = map[i];
		}
		free(map);
	}
	return (ret);
}

void	realloc_list(t_room **head, int size)
{
	t_room	*new_head;
	int		i;

	i = -1;
	new_head = (t_room *)malloc(sizeof(t_room) * (size + 2000));
	while ((*head) && (*head)[++i].name)
	{
		new_head[i] = (*head)[i];
		new_head[i].link = NULL;
		new_head[i].name = ft_strdup((*head)[i].name);
		new_head[i + 1].name = NULL;
		ft_strdel(&(*head)[i].name);
	}
	if (size == 2000)
		new_head[0].name = NULL;
	else
		new_head[i].name = NULL;
	if ((*head))
		free((*head));
	(*head) = new_head;
}

size_t	*new_sizet_tab(int size)
{
	size_t		*ret;
	int			cur;

	cur = -1;
	ret = (size_t *)malloc(sizeof(size_t) * (size + 10));
	while (++cur < (size + 10))
		ret[cur] = 0;
	return (ret);
}

size_t	*realloc_links(t_room *tmp)
{
	size_t	*ret;
	int		i;

	i = 0;
	ret = new_sizet_tab(tmp->size + 10);
	while ((tmp->link) && tmp->link[i])
	{
		ret[i] = tmp->link[i];
		i++;
	}
	while (i < tmp->size + 9)
		ret[i++] = 0;
	if ((tmp->link))
		free(tmp->link);
	return (ret);
}

t_way	*new_roads(int size)
{
	t_way	*res;
	int		i;

	i = -1;
	res = (t_way *)malloc(sizeof(t_way) * (size + 5));
	while (++i < (size + 5))
		res[i] = empty_way();
	return (res);
}
