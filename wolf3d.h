/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drosa-ta <drosa-ta@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 01:15:30 by drosa-ta          #+#    #+#             */
/*   Updated: 2018/04/25 00:24:48 by drosa-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include <SDL2/SDL.h>
# include <SDL2/SDL_mixer.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 1024
# define MAP_WIDTH 24
# define MAP_HEIGHT 24
# define BUFF_SIZE 4096
# define PLAYER_START_X 22
# define PLAYER_START_Y 12

typedef struct	s_player
{
	double pos_x;
	double pos_y;
	double dir_x;
	double dir_y;
	double plane_x;
	double plane_y;
	double move_speed;
	double rot_speed;
}				t_player;

typedef struct	s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	bool	is_x_side;
	int		step_x;
	int		step_y;
	double	length;
}				t_ray;

typedef struct	s_line
{
	int		height;
	int		start;
	int		end;
	Uint32	color;
}				t_line;

void			init_player(t_player *player);
double			dist_to_wall(t_ray *ray, t_player player, int **world_map);
void			set_line(t_line *line, bool is_x_side, int wall);
void			draw_pixels(int x, t_line line, Uint32 **buffer);
void			draw_screen(SDL_Renderer *ren, Uint32 **buff, SDL_Texture *tex);
void			set_player_pos(t_player *player, int **world_map);
bool			put_error(char *str);
bool			is_input_key(SDL_Keycode key);
bool			done(bool quit_if_esc, bool delay, Mix_Music *music);
char			*ft_file_to_str(const char *file_name);
double			get_frametime(void);
void			set_boundary(int **map, int w, int h);

#endif
