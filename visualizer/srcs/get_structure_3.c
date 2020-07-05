/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_structure_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 19:00:08 by selly             #+#    #+#             */
/*   Updated: 2020/02/19 19:01:02 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

t_begin		*full_rooms_coord(char *line, t_begin *new, int *s_e)
{
	char	*s;

	s = (char *)malloc(sizeof(char) * ft_strlen(line) + 1);
	s = ft_strcpy(s, line);
	new->str = s;
	new->type = *s_e;
	if (*s_e > 0 && s[0] != 'L')
	{
		*s_e = 3;
		while (*line && *line != ' ' && *line != '-')
		{
			line++;
		}
		if (*line == ' ')
			new->read = 1;
		if (*line == '-')
			new->read = 2;
	}
	if (s[0] == 'L')
	{
		new->read = 3;
		new->type = 0;
	}
	return (new);
}

void		free_begin(t_begin **pointer)
{
	t_begin	*n;

	while (*pointer)
	{
		n = (*pointer)->next;
		if ((*pointer)->str)
			free((*pointer)->str);
		ft_memdel((void **)pointer);
		(*pointer) = n;
	}
}

void		free_memory(char **line, t_begin **head)
{
	if (*head)
		free_begin(head);
	if (*line)
		ft_strdel(line);
}

t_begin		*new_begin(void)
{
	t_begin	*begin;

	if (!(begin = (t_begin *)ft_memalloc(sizeof(t_begin))))
		print_error("Malloc error.");
	begin->str = NULL;
	begin->type = 0;
	begin->read = 0;
	return (begin);
}
