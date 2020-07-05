/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:20:49 by selly             #+#    #+#             */
/*   Updated: 2020/02/21 17:03:19 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

char		*check_num_ants(char **param, int *stage)
{
	if (param[0] && param[1])
		return ("ERROR\n");
	if (!(ft_str_is_number(param[0])))
		return ("ERROR\n");
	if (ft_strlen(param[0]) > 7)
		return ("ERROR\n");
	if (ft_atoi(param[0]) > 2000000)
		return ("ERROR\n");
	if (ft_atoi(param[0]) < 0)
		return ("ERROR\n");
	if (ft_atoi(param[0]) == 0)
		return ("ERROR\n");
	(*stage)++;
	return (NULL);
}

char		*same_param(t_room *head, char **param)
{
	int		i_1;
	int		i_2;
	int		i_3;

	i_1 = -1;
	i_2 = ft_atoi(param[1]);
	i_3 = ft_atoi(param[2]);
	while (head && head[++i_1].name)
	{
		if (!(ft_strcmp(head[i_1].name, param[0])))
			return ("ERROR\n");
		if (head[i_1].coord.x == i_2 && head[i_1].coord.y == i_3)
			return ("ERROR\n");
	}
	return (NULL);
}

char		*check_coords(t_room *head, char **param)
{
	char	*line;

	if (param[0] && param[1] && param[2] && param[3])
		return ("ERROR\n");
	if (!(param[0]) || !(param[1]) || !(param[2]))
		return ("ERROR\n");
	if (ft_strcmp(param[0], "L") == 0)
		return ("ERROR\n");
	if (!(ft_str_is_number(param[1])))
		return ("ERROR\n");
	if (!(ft_str_is_number(param[2])))
		return ("ERROR\n");
	if (ft_atoi(param[1]) < 0)
		return ("ERROR\n");
	if (ft_atoi(param[2]) < 0)
		return ("ERROR\n");
	if ((line = same_param(head, param)))
		return (line);
	return (NULL);
}

char		*check_edges(t_room *h, char **p)
{
	char	*str;
	int		i_1;
	int		i_2;

	i_1 = 0;
	i_2 = 0;
	if (p[0] && p[1])
		return ("ERROR\n");
	if (!(str = ft_strchr(p[0], '-')))
		return ("ERROR\n");
	if (!(ft_strncmp(p[0], (str + 1), ft_strlen(str + 1)))
			&& p[0][ft_strlen(str + 1)] == '-')
		return ("ERROR\n");
	while (h[i_1].name && (ft_strncmp(h[i_1].name,
					p[0], h[i_1].len) || p[0][h[i_1].len] != '-'))
		i_1++;
	if (!(h[i_1].name))
		return ("ERROR\n");
	while (h[i_2].name && (ft_strncmp(h[i_2].name,
		(p[0] + (h[i_1].len + 1)), h[i_2].len) || ft_strncmp(h[i_2].name,
		(p[0] + (h[i_1].len + 1)), ft_strlen(p[0] + (h[i_1].len + 1)))))
		i_2++;
	if (!(h[i_2].name))
		return ("ERROR\n");
	return (NULL);
}

char		*check_error_p(t_room *head, char **param, int *stage)
{
	char	*line;

	if (!(param[0]))
		return ("ERROR\n");
	if (param[0][0] == '#')
		return (NULL);
	if ((*stage == 1) && (ft_strchr(param[0], '-') && !(param[1])))
	{
		if (!head)
			return ("ERROR\n");
		if ((line = check_start_end_find(head)))
			return (line);
		++(*stage);
	}
	if (*stage == 0)
		return (check_num_ants(param, stage));
	if (*stage == 1)
		return (check_coords(head, param));
	if (*stage == 2)
		return (check_edges(head, param));
	return (NULL);
}
