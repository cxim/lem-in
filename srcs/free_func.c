/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:27:55 by selly             #+#    #+#             */
/*   Updated: 2020/02/19 18:09:40 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		ft_tabdel(char **tab)
{
	int		cur;

	cur = -1;
	if (!tab)
		return ;
	while (tab[++cur])
		ft_strdel(&tab[cur]);
	free(tab);
	tab = NULL;
}

void		free_struct(t_room *head)
{
	int		i;

	i = -1;
	while (head && head[++i].name)
	{
		if (head[i].link)
			free(head[i].link);
		free(head[i].name);
	}
	if (head)
		free(head);
}

int			pars_free_all(char ***param, char ***res, t_room **head)
{
	if (param)
	{
		ft_tabdel(*(param));
		*(param) = NULL;
	}
	if (res)
	{
		ft_tabdel(*(res));
		*(res) = NULL;
	}
	if (head)
	{
		free_struct(*(head));
		*(head) = NULL;
	}
	get_next_line(-1, NULL);
	return (6);
}

void		free_roads(t_way *head)
{
	int		i;

	i = -1;
	while (head[++i].road)
		free(head[i].road);
	if (head)
		free(head);
}

void		free_all(t_room **head, t_way **road, t_way **ways)
{
	if (*(head))
		free_struct(*(head));
	if (*(road))
		free_roads(*(road));
	if (*(ways))
		free(*(ways));
}
