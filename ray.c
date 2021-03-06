/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drosa-ta <drosa-ta@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 00:19:23 by drosa-ta          #+#    #+#             */
/*   Updated: 2018/02/08 00:19:25 by drosa-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		set_boundary(int **map, int w, int h)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < h)
	{
		while (j < w)
		{
			if ((i == 0 && j < w) || (i < h && j == 0) ||
				(j == w - 1 && i < h) || (i == h - 1 && j < w))
				map[i][j] = 1;
			j++;
		}
		j = 0;
		i++;
	}
}

void		init_player(t_player *player)
{
	player->pos_x = PLAYER_START_X;
	player->pos_y = PLAYER_START_Y;
	player->dir_x = -1;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0.66;
}

static void	set_ray(t_ray *ray, t_player player)
{
	ray->dir_x = player.dir_x + player.plane_x * ray->camera_x;
	ray->dir_y = player.dir_y + player.plane_y * ray->camera_x;
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player.pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1 - player.pos_x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player.pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1 - player.pos_y) * ray->delta_dist_y;
	}
}

static void	cast_ray(t_ray *ray, int **world_map)
{
	bool is_wall;

	is_wall = false;
	while (!is_wall)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->is_x_side = true;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->is_x_side = false;
		}
		if (world_map[ray->map_x][ray->map_y] > 0)
			is_wall = true;
	}
}

double		dist_to_wall(t_ray *ray, t_player player, int **world_map)
{
	double ray_len;

	ray->map_x = (int)player.pos_x;
	ray->map_y = (int)player.pos_y;
	set_ray(ray, player);
	cast_ray(ray, world_map);
	if (ray->is_x_side)
		ray_len =
			(ray->map_x - player.pos_x + (1 - ray->step_x) / 2) / ray->dir_x;
	else
		ray_len =
			(ray->map_y - player.pos_y + (1 - ray->step_y) / 2) / ray->dir_y;
	return (ray_len);
}
