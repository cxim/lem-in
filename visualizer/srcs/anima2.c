/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anima2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 18:49:48 by selly             #+#    #+#             */
/*   Updated: 2020/02/19 18:50:39 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

int				put_biglem(t_draw *draw, int x, int y, int color)
{
	int			w;
	int			buf;
	int			h;

	h = 4;
	buf = x;
	while (h)
	{
		w = 4;
		while (w)
		{
			put_pixel(draw, x, y, color);
			x++;
			w--;
		}
		x = buf;
		y++;
		h--;
	}
	return (1);
}

void			put_lem(t_point f, t_point s, t_draw *d, int c)
{
	t_point		delta;
	t_point		sign;
	t_point		cur;
	int			error[2];

	delta.x = (s.x - f.x) < 0 ? -(s.x - f.x) : (s.x - f.x);
	delta.y = (s.y - f.y) < 0 ? -(s.y - f.y) : (s.y - f.y);
	sign.x = f.x < s.x ? 1 : -1;
	sign.y = f.y < s.y ? 1 : -1;
	error[0] = delta.x - delta.y;
	cur = f;
	if ((cur.x != s.x || cur.y != s.y))
	{
		put_biglem(d, cur.x, cur.y, c);
		if ((error[1] = error[0] * 2) > -delta.y)
		{
			error[0] -= delta.y;
			cur.x += sign.x;
		}
		if (error[1] < delta.x)
		{
			error[0] += delta.x;
			cur.y += sign.y;
		}
	}
}

void			lem_go(t_begin *read, t_map **map, t_draw *draw)
{
	char		*line;
	int			count;

	(*map)->move += 1;
	count = (*map)->move;
	if ((*map)->move <= (*map)->max_move && count)
	{
		count = (*map)->move;
		while (read->next && count)
		{
			if (read->read == 3)
			{
				while (count && read->next)
				{
					line = read->str;
					read = read->next;
					count--;
				}
			}
			if (read->next && count)
				read = read->next;
		}
	}
	if (*line)
		change_position(line, &(*map), draw);
}
