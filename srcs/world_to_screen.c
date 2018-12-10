/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_to_screen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 09:03:37 by hbally            #+#    #+#             */
/*   Updated: 2018/12/10 20:47:56 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf.h"

static void			pt_to_canvas(t_vector *point, t_camera *cam)
{
	vect_mat_mul(point, cam->t.matrix);
	point->x /= -point->z;
	point->y /= -point->z;
	if (!(point->z >= -0.1))
		point->z = 1;
	else
		point->z = 0;
}

static void			pt_to_screen(t_vector *point, t_camera *cam, t_img *img)
{
	point->x = (point->x + cam->canvas_w / 2) / cam->canvas_w;
	point->y = (point->y + cam->canvas_h / 2) / cam->canvas_h;
	point->x = floor((double)(point->x * img->win_width));
	point->y = floor((double)((1 - point->y) * img->win_height));
}

static void			pt_draw(t_vector *point, t_hub *hub, int z, int x)
{
	t_vector		connected_point;

	if (x < hub->map->width - 1)
	{
		connected_point = hub->map->points[z][x + 1];
		pt_to_canvas(&connected_point, &(hub->camera));
		if (point->z && connected_point.z)
		{
			pt_to_screen(&connected_point, &(hub->camera), &(hub->img));
			//fix
			draw_line(&(hub->img), *point, connected_point, hub);
		}
	}
	if (z > 0)
	{
		connected_point = hub->map->points[z][x + 1];
		connected_point = hub->map->points[z - 1][x];
		pt_to_canvas(&connected_point, &(hub->camera));
		if (point->z && connected_point.z)
		{
			pt_to_screen(&connected_point, &(hub->camera), &(hub->img));
			//fix
			draw_line(&(hub->img), *point, connected_point, hub);
		}
	}
}

void				world_to_screen(t_hub *hub)
{
	int 			x;
	int				z;
	t_vector		point;

	z = 0;
	x = 0;
	while (z < hub->map->height)
	{
		x = 0;
		while (x < hub->map->width)
		{
			point = hub->map->points[z][x];
			pt_to_canvas(&point, &(hub->camera));
			if (hub->camera.fullrender ||
					!((double)fabs(point.x) > hub->camera.canvas_w / 2 ||
						(double)fabs(point.y) > hub->camera.canvas_h / 2))
			{
				pt_to_screen(&point, &(hub->camera), &(hub->img));
				pt_draw(&point, hub, z, x);
			}
			x++;
		}
		z++;
	}
}
