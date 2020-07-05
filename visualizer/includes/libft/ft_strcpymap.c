/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpymap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 15:52:01 by selly             #+#    #+#             */
/*   Updated: 2019/05/04 15:53:30 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strcpymap(char const *s, char **m, char c)
{
	int		i;
	int		a;

	i = 0;
	a = 0;
	if (!s && !m)
		return (NULL);
	while (*s == c)
		s++;
	while (*s)
	{
		if (*s != c)
		{
			m[i][a] = *s;
			a++;
		}
		else if (*s == c && *(s + 1) != '\0' && *(s + 1) != c)
		{
			i++;
			a = 0;
		}
		s++;
	}
	return (m);
}
