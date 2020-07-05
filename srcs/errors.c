/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:19:56 by selly             #+#    #+#             */
/*   Updated: 2020/02/19 17:20:33 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

char		**free_map(char **map)
{
	int		i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	if (map)
		free(map);
	map = NULL;
	return (map);
}

int			check_end(t_room *head)
{
	int		res;
	int		i;

	i = -1;
	res = 0;
	while (head[++i].name)
		res += head[i].end;
	return (res);
}

int			check_start(t_room *head)
{
	int		res;
	int		i;

	i = -1;
	res = 0;
	while (head[++i].name)
		res += head[i].start;
	return (res);
}

char		*check_start_end_find(t_room *head)
{
	int		start;
	int		end;

	end = check_end(head);
	start = check_start(head);
	if (end == 1 && start == 1)
		return (NULL);
	else
		return ("ERROR\n");
}
