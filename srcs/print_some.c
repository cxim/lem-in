/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_some.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:33:01 by selly             #+#    #+#             */
/*   Updated: 2020/02/19 18:06:50 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		*print_error_parse(char *line, int line_num, int stage)
{
	line_num = line_num + 1;
	stage = stage + 1;
	ft_putstr_fd(line, 2);
	return (NULL);
}

char		**print_map(char **str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		ft_putstr(str[i]);
		write(1, "\n", 1);
		free(str[i]);
	}
	write(1, "\n", 1);
	if (str)
		free(str);
	str = NULL;
	return (NULL);
}

void		print_one_way(t_room *head, int i_ants)
{
	t_room	*end;
	int		i;

	end = head;
	i = i_ants;
	while (!(end->end))
		end++;
	while (--i > 0)
	{
		ft_printf("L%d-%s ", (i_ants - i), end->name);
	}
	ft_printf("L%d-%s\n", (i_ants - i), end->name);
}

void		print_and_move(t_way *head, int i, int j, int *k)
{
	t_room	*tmp1;
	t_room	*tmp2;

	tmp1 = ((t_room *)(head->road[j]));
	tmp2 = ((t_room *)(head->road[j + 1]));
	if (!(tmp1->num_ants) || !(head->value) || ((tmp1->start) && !(head->ants)))
		return ;
	if (tmp1->start)
	{
		tmp2->name_ants = (i - (--(tmp1->num_ants)));
		head->ants--;
	}
	else
	{
		tmp1->num_ants = 0;
		tmp2->name_ants = tmp1->name_ants;
		tmp1->name_ants = 0;
	}
	tmp2->num_ants = (tmp2->end) ? 0 : 1;
	if (*k)
		ft_printf(" ");
	ft_printf("L%d-%s", tmp2->name_ants, tmp2->name);
	*k = 1;
}

void		print_way_group(t_way *top_way, int n_ants)
{
	int		i;
	int		j;
	int		k;

	k = 0;
	i = -1;
	if (!(stay_on(top_way)))
		return ;
	while (top_way[++i].road)
	{
		j = top_way[i].len;
		while (--j >= 0)
			print_and_move((top_way + i), n_ants, j, &k);
		if (top_way[i].value)
			top_way[i].value--;
	}
	if (k)
		ft_printf("\n");
	print_way_group(top_way, n_ants);
}
