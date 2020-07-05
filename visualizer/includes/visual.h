/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 18:38:13 by selly             #+#    #+#             */
/*   Updated: 2020/02/19 18:46:40 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUAL_H
# define VISUAL_H

# include "libft/libft.h"
# include "mlx.h"
# include <math.h>

typedef	enum
{
	ISOMETRIC,
	PARALLEL
}	t_projection;

typedef struct			s_begin
{
	char				*str;
	int					type;
	int					read;
	struct s_begin		*next;
}						t_begin;

typedef struct			s_mouse
{
	int					x;
	int					y;
	int					next_x;
	int					next_y;
	int					but_pressed;
}						t_mouse;

typedef struct			s_camera
{
	t_projection		projection;
	int					zoom;
	double				alpha;
	double				beta;
	double				gamma;
	float				z_divisor;
	int					x_offset;
	int					y_offset;
}						t_camera;

typedef struct			s_map
{
	struct s_begin		*read;
	int					max_move;
	int					move;
	int					ants;
	int					ants_start;
	int					ants_finish;
	struct s_lemings	*lems;
	int					width;
	int					z_min;
	int					z_max;
	int					len;
	int					height;
	int					frame;
	int					back;
	int					*z_array;
	int					*color_array;
	int					go;
}						t_map;

typedef struct			s_draw
{
	void				*mlx_ptr;
	void				*win_ptr;
	void				*img_ptr;
	char				*data_addres;
	int					bits_per_pixel;
	int					size_line;
	int					endian;
	int					w_window;
	int					h_window;
	int					menu;
	int					i;
	int					iso_p;
	int					s_x;
	int					s_y;
	int					flag_move_mouse;
	int					flag_iso_par;
	int					speed;
	struct s_draw		*draw;
	t_camera			*null_camera;
	t_camera			*camera;
	t_mouse				*mouse;
	struct s_map		*s_map;
}						t_draw;

typedef struct			s_point
{
	int					x;
	int					y;
	int					z;
	int					color;
}						t_point;

typedef struct			s_lemings
{
	int					x_pos;
	int					y_pos;
	int					x_go;
	int					y_go;
	int					in_start;
	int					in_finish;
	struct s_lemings	*next;
}						t_lemings;

void					lem_go(t_begin *read, t_map **map, t_draw *draw);
int						from(char *links, t_begin *room, int flag, int go);
int						to(char *links, t_begin *room, int flag);
void					draw_line(t_point f, t_point s, t_draw *draw);
void					put_lems(t_map *map, t_draw *draw, int ants);
void					put_links(t_map *map, t_draw *draw);
int						main(void);
t_point					new_point(int x, int y, t_map *map, int flag);
int						get_moves(t_begin *read);
void					put_pixel(t_draw *draw, int x, int y, int color);
t_lemings				*new_lems(t_begin *n, int ants, int x);
int						get_troom(t_begin *read, char coord, int type);
void					lem_go(t_begin	*read, t_map **map, t_draw *draw);
void					put_name(t_point a, t_draw *draw, char *name);
t_begin					*new_begin(void);
void					free_begin(t_begin **pointer);
int						get_xy(char *s, int flag);
void					change_position(char *line, t_map **map, t_draw *draw);
void					free_memory(char **line, t_begin **head);
void					parser_lemin(t_begin *n, int ants);
int						type_of_room(char *line);
t_begin					*full_rooms_coord(char *line, t_begin *n, int *s_e);
void					start_visual(t_map *map, char *screen, char *speed);
void					put_lem(t_point f, t_point s, t_draw *draw, int color);
void					print_error(char *error);
t_map					*new_map(t_begin *n, int max_x, int max_y, int ants);
t_draw					*new_draw(t_map *map, char *scr, t_mouse *m, char *sp);
t_camera				*new_camera(t_draw *draw, t_map *map);
t_mouse					*new_mouse(void);
void					start_draw(t_map *map, t_draw *draw, int x, int y);
void					text_menu(t_draw *draw);
int						key_press(int key, t_draw *draw);
int						mouse_move(int x, int y, t_draw *draw);
int						mouse_release(int button, int x, int y, t_draw *draw);
int						mouse_press(int button, int x, int y, t_draw *draw);
t_camera				*c_cam(t_draw *draw);
int						close_win(t_draw **draw);
int						iso_par(t_draw *draw, int p);
int						g_color(t_point c, t_point st, t_point e, t_point delt);
int						get_default_color(int z, t_map *map);
int						zoom(t_draw *draw, int zoom);
t_point					project(t_point p, t_draw *draw);
void					text_menu(t_draw *draw);
int						control_color(int i, int m);

#endif
