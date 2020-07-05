/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:29:55 by selly             #+#    #+#             */
/*   Updated: 2020/02/21 15:26:52 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int				have_connect(t_way *roads, t_way road_tmp)
{
	int			i;
	int			j;
	int			k;

	i = -1;
	while (roads[++i].road)
	{
		j = 0;
		while (roads[i].road[++j + 1])
		{
			k = 0;
			while (road_tmp.road[++k + 1])
				if (roads[i].road[j] == road_tmp.road[k])
					return (1);
		}
	}
	return (0);
}

char			*end_or_start(char *line, char *tmp)
{
	static int	stop = 0;

	if (!(ft_strcmp(line, START)) && (stop = 1))
		return (START);
	if (!(ft_strcmp(line, END)) && (stop = 1))
		return (END);
	if (line[0] == '#')
		return (tmp);
	if (stop++ == 1)
		return (tmp);
	stop = 0;
	return (NULL);
}

int				ch_err(int stage, int cur)
{
	if (stage == 1 && cur != 6)
		return (0);
	return (1);
}

int				empty(int st, int c, char **p, char *l)
{
	if (st == 0 && c == 0 && p == NULL && l == NULL)
		return (1);
	return (0);
}

char			**pars_map(t_room **ret, int fd, int st, int c)
{
	char		**res;
	char		**p;
	char		*l;
	char		*tmp;

	res = realloc_map(NULL, c);
	while (get_next_line(fd, &(res[++c])) > 0)
	{
		if ((c) && (c % 2000) == 0)
			res = realloc_map(res, c);
		if (ft_strlen_mod(res[c]) == 0 && ft_printf("ERROR\n")
			&& (c = pars_free_all(NULL, &res, ret)))
			break ;
		p = ft_strsplit(res[c], ' ');
		tmp = end_or_start(res[c], tmp);
		if ((l = check_error_p(*ret, p, &st))
			&& pars_free_all(&p, &res, ret))
			return (print_error_parse(l, c, st));
		if (p[0][0] != '#')
			fill_room(ret, p, tmp, st);
		ft_tabdel(p);
	}
	if (st == 1 || (empty(st, c, p, l) && ft_printf("ERROR\n")))
		pars_free_all(NULL, &res, ret);
	return (ch_err(st, c) == 1 ? res : print_error_parse("ERROR\n", c, 2));
}
