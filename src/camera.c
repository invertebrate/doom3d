/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/10 14:21:37 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Calculates plane normals for top, right, bottom and left.
** These are used in object culling. dot(player to aabb min & max, normal)
*/

static void		set_side_plane_normals(t_doom3d *app, t_camera *camera,
					t_vec3 corners[4])
{
	t_vec3	tmp[2];

	ml_vector3_sub(corners[3], app->player.pos, tmp[0]);
	ml_vector3_sub(corners[0], app->player.pos, tmp[1]);
	ml_vector3_cross(tmp[1], tmp[0], camera->viewplanes[1].normal);
	ml_vector3_normalize(camera->viewplanes[1].normal,
		camera->viewplanes[1].normal);
	ml_vector3_sub(corners[0], app->player.pos, tmp[0]);
	ml_vector3_sub(corners[1], app->player.pos, tmp[1]);
	ml_vector3_cross(tmp[1], tmp[0], camera->viewplanes[2].normal);
	ml_vector3_normalize(camera->viewplanes[2].normal,
		camera->viewplanes[2].normal);
	ml_vector3_sub(corners[1], app->player.pos, tmp[0]);
	ml_vector3_sub(corners[2], app->player.pos, tmp[1]);
	ml_vector3_cross(tmp[1], tmp[0], camera->viewplanes[3].normal);
	ml_vector3_normalize(camera->viewplanes[3].normal,
		camera->viewplanes[3].normal);
	ml_vector3_sub(corners[2], app->player.pos, tmp[0]);
	ml_vector3_sub(corners[3], app->player.pos, tmp[1]);
	ml_vector3_cross(tmp[1], tmp[0], camera->viewplanes[4].normal);
	ml_vector3_normalize(camera->viewplanes[4].normal,
		camera->viewplanes[4].normal);
}

/*
**	Sets camera viewbox using planes. The order is:
**	Near, top, right, bottom, left
** 	// http://davidlively.com/programming/graphics/
** frustum-calculation-and-culling-hopefully-demystified/
** Corners: ne, se, sw, nw.
** How?: Get screen origin, traverse to corners to get corner vectors,
** cross product nearby corners to get plane normals.
*/

static void		set_camera_viewbox(t_doom3d *app, t_camera *camera)
{
	t_vec3	dirs[4];
	t_vec3	corners[4];
	t_vec3	screen_origin;
	t_vec3	add;
	float	dims[2];

	dims[0] = app->window->framebuffer->width / 2.0;
	dims[1] = app->window->framebuffer->height / 2.0;
	ml_vector3_copy(app->player.forward, camera->viewplanes[0].normal);
	ml_vector3_mul(app->player.forward,
		ml_vector3_mag(camera->screen.origin), add);
	ml_vector3_add(app->player.pos, add, screen_origin);
	ml_vector3_mul(app->player.up, dims[1], dirs[0]);
	ml_vector3_mul(app->player.sideways, dims[0], dirs[1]);
	ml_vector3_mul(app->player.up, -dims[1], dirs[2]);
	ml_vector3_mul(app->player.sideways, -dims[0], dirs[3]);
	ml_vector3_add(screen_origin, dirs[0], corners[0]);
	ml_vector3_add(corners[0], dirs[1], corners[0]);
	ml_vector3_add(screen_origin, dirs[1], corners[1]);
	ml_vector3_add(corners[1], dirs[2], corners[1]);
	ml_vector3_add(screen_origin, dirs[2], corners[2]);
	ml_vector3_add(corners[2], dirs[3], corners[2]);
	ml_vector3_add(screen_origin, dirs[3], corners[3]);
	ml_vector3_add(corners[3], dirs[0], corners[3]);
	set_side_plane_normals(app, camera, corners);
}

void			update_camera(t_doom3d *app)
{
	t_camera	*camera;

	camera = app->active_scene->main_camera;
	camera->near_clip = -NEAR_CLIP_DIST;
	camera->far_clip = -FAR_CLIP_DIST;
	ml_vector3_set(camera->screen.origin, 0, 0,
		-app->window->framebuffer->width * 0.7);
	ml_vector3_set(camera->screen.normal, 0, 0, 1);
	set_camera_viewbox(app, camera);
}

t_camera		*new_camera(void)
{
	t_camera	*camera;

	if (!(camera = (t_camera*)malloc(sizeof(t_camera))))
		return (NULL);
	ml_vector3_set_all(camera->origin, 0);
	return (camera);
}

void			scene_camera_destroy(t_scene *scene)
{
	if (scene->main_camera)
	{
		free(scene->main_camera);
		scene->main_camera = NULL;
	}
}
