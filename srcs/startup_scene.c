/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startup_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 10:00:58 by hbally            #+#    #+#             */
/*   Updated: 2018/12/12 18:11:47 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf.h"
#include "libft.h"
#include "matrix.h"
#include "colors.h"

void			reset_canvas(t_camera *camera)
{
	if (camera->projection == 1)
	{
		camera->canvas_w = 2;
		camera->canvas_h = 2;
	}
	else
	{
		camera->canvas_w = 20;
		camera->canvas_h = 20;
	}
}

void			startup_camera(t_camera *camera, t_map *map)
{
	ft_bzero(&(camera->t), sizeof(t_transform));
	reset_canvas(camera);
	if (camera->projection == 1)
		camera->speed = 2 * map->width;
	else
		camera->speed = 8 * map->width;

	camera->t.translate_x = (float)map->width / 2;
	camera->t.translate_z = (float)map->height / 2;
	/*
	camera->t.rotate_x = -M_PI / 3;
	camera->t.rotate_y = -atan((double)map->width / (double)map->height);
	camera->t.translate_x = -(float)map->width;
	camera->t.translate_y = (float)map->width;
	camera->t.translate_z = (float)map->height;
	*/
}

void			startup_map(t_map *map,
							float delta_elevation,
							float delta_scale)
{
	matrix_inv(map->t.matrix);
	transform_apply(&(map->t), map->points, map->width, map->height);
	map->t.scale_x += delta_scale;
	map->t.scale_y += delta_elevation;
	map->t.scale_z += delta_scale;
	if (map->t.scale_x < 0.1)
		map->t.scale_x = 0.1;
	if (map->t.scale_z < 0.1)
		map->t.scale_z = 0.1;
	if (map->t.scale_y == 0)
		map->t.scale_y += delta_elevation;
	transform_build(&(map->t));
	transform_apply(&(map->t), map->points, map->width, map->height);
}

void			startup_scene(t_hub *hub)
{
	ft_bzero(&(hub->camera), sizeof(t_camera));

	hub->camera.projection = 1;
	hub->camera.fullrender = 0;
	map_assign_altitude(hub->map, 1);

	hub->img.background_color = PASTEL_WHITE;
	hub->img.night_mode = 1;
	hub->img.show_ui = 0;

	startup_map(hub->map, 0.5, 1);
	startup_camera(&(hub->camera), hub->map);
}
