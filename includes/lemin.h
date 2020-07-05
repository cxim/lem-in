/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 18:22:18 by selly             #+#    #+#             */
/*   Updated: 2020/02/19 18:34:06 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H
# define END "##end"
# define START "##start"
# include "printf.h"

typedef struct		s_way
{
	size_t			*road;
	int				value;
	int				ants;
	int				len;
}					t_way;

typedef struct		s_pos
{
	int				x;
	int				y;
}					t_pos;

typedef struct		s_dieks
{
	size_t			room;
	int				done;
	int				len;
}					t_dieks;

typedef struct		s_room
{
	char			*map;
	size_t			*link;
	char			*name;
	int				len;
	int				end;
	int				size;
	int				start;
	int				num_ants;
	int				name_ants;
	t_pos			coord;
	t_dieks			dieks;
}					t_room;

int					have_connect(t_way *roads, t_way road_tmp);
char				**free_map(char **map);
void				i_prms(t_room **s1, t_way **s2, t_way **s3, char ***s4);
t_way				get_dieks(t_room *end);
t_room				*new_ptr_dieks(t_room *head, t_room *tmp);
char				**new_tab(int size);
char				*check_edges(t_room *head, char **param);
char				*check_coords(t_room *head, char **param);
char				*same_param(t_room *head, char **param);
char				**pars_map(t_room **ret, int fd, int stage, int cur);
char				**realloc_map(char **map, int size);
char				*check_start_end_find(t_room *head);
char				*check_num_ants(char **param, int *stage);
char				*check_error_p(t_room *head, char **param, int *stage);
int					pars_free_all(char ***param, char ***res, t_room **head);
void				*print_error_parse(char *line, int line_num, int stage);
void				ft_tabdel(char **tab);
void				fill_room(t_room **h, char **p, char *tmp, int stage);
void				realloc_list(t_room **head, int size);
size_t				*realloc_links(t_room *tmp);
t_room				*find_end(t_room *head);
t_room				*find_start(t_room *head);
t_way				best_way(t_room *head);
size_t				*new_sizet_tab(int size);
char				**print_map(char **str);
void				print_one_way(t_room *head, int i_ants);
int					find_num_ants(t_room *head);
void				free_struct(t_room *head);
t_way				*find_ways_di(t_room *head);
t_way				*new_roads(int size);
t_way				empty_way(void);
int					find_num_ways(t_room *head);
t_way				*best_way_group(t_way *head, int n_ants);
int					find_nbr_roads(t_way *head);
int					count_turn_solve(t_way *head, int n_ants);
void				print_way_group(t_way *top_way, int n_ants);
int					stay_on(t_way *head);
void				free_all(t_room **head, t_way **road, t_way **ways);
void				free_roads(t_way *head);
#endif
