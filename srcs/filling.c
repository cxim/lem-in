/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:22:49 by selly             #+#    #+#             */
/*   Updated: 2020/02/19 17:26:46 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			add_room(t_room **old_head, char **param)
{
	static int	size = 2000;
	int			i;

	i = 0;
	if ((size % 2000) == 0)
		realloc_list(old_head, size);
	while ((*old_head) && (*old_head)[i].name)
		i++;
	(*old_head)[i].end = 0;
	(*old_head)[i].size = 200;
	(*old_head)[i].start = 0;
	(*old_head)[i].link = NULL;
	(*old_head)[i].num_ants = 0;
	(*old_head)[i].len = ft_strlen(param[0]);
	(*old_head)[i].name = ft_strdup(param[0]);
	(*old_head)[i].coord.x = ft_atoi(param[1]);
	(*old_head)[i].coord.y = ft_atoi(param[2]);
	(*old_head)[i].dieks.len = 0;
	(*old_head)[i].dieks.done = 0;
	(*old_head)[i].dieks.room = 0;
	(*old_head)[i + 1].name = NULL;
	size++;
}

void			get_start_end(t_room *head, char *tmp, int nb_ants)
{
	int			i;

	i = -1;
	if (!(tmp))
		return ;
	while (head[i + 1].name)
		i++;
	if (!(ft_strcmp(tmp, START)))
	{
		head[i].start = 1;
		head[i].num_ants = nb_ants;
	}
	if (!(ft_strcmp(tmp, END)))
		head[i].end = 1;
}

int				len_i(t_room *head, int i_1, int l1, char *s1)
{
	while (head[i_1].name && (head[i_1].len != l1 ||
		ft_strncmp(head[i_1].name, s1, head[i_1].len)))
		i_1++;
	return (i_1);
}

void			add_links(t_room *head, char **param, int l1, int l2)
{
	int			i_1;
	int			i_2;
	int			i_3;
	char		*s1;
	char		*s2;

	i_1 = 0;
	i_2 = 0;
	s1 = param[0];
	s2 = ft_strchr(s1, '-') + 1;
	i_1 = len_i(head, i_1, l1, s1);
	i_2 = len_i(head, i_2, l2, s2);
	if ((head[i_1].size++ % 10) == 0)
		head[i_1].link = realloc_links((head + i_1));
	if ((head[i_2].size++ % 10) == 0)
		head[i_2].link = realloc_links((head + i_2));
	i_3 = 0;
	while (head[i_1].link && head[i_1].link[i_3])
		i_3++;
	head[i_1].link[i_3] = (size_t)(head + i_2);
	i_3 = 0;
	while (head[i_2].link && head[i_2].link[i_3])
		i_3++;
	head[i_2].link[i_3] = (size_t)(head + i_1);
}

void			fill_room(t_room **head, char **param, char *tmp, int stage)
{
	static int	save_num_ants = 0;
	int			l1;
	int			l2;
	char		*s1;
	char		*s2;

	if (!(save_num_ants) && (save_num_ants = ft_atoi(param[0])))
		return ;
	if (stage == 1)
	{
		add_room(head, param);
		get_start_end(*head, tmp, save_num_ants);
	}
	if (stage == 2)
	{
		s1 = param[0];
		s2 = ft_strchr(s1, '-') + 1;
		l1 = (int)(s2 - s1 - 1);
		l2 = ft_strlen(s2);
		add_links(*head, param, l1, l2);
	}
}
