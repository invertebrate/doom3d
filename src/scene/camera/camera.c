/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/04 16:28:34 by sotamursu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Calculates plane normals for top, right, bottom and left.
** These are used in object culling. dot(player to aabb min & max, normal)
*/

static void	set_side_plane_normals(t_camera *camera,
					t_vec3 corners[4], t_vec3 pos)
{
	t_vec3	tmp[2];

	ml_vector3_sub(pos, corners[3], tmp[0]);
	ml_vector3_sub(pos, corners[0], tmp[1]);
	ml_vector3_cross(tmp[0], tmp[1], camera->viewplanes[1].normal);
	ml_vector3_normalize(camera->viewplanes[1].normal,
		camera->viewplanes[1].normal);
	ml_vector3_sub(pos, corners[0], tmp[0]);
	ml_vector3_sub(pos, corners[1], tmp[1]);
	ml_vector3_cross(tmp[0], tmp[1], camera->viewplanes[2].normal);
	ml_vector3_normalize(camera->viewplanes[2].normal,
		camera->viewplanes[2].normal);
	ml_vector3_sub(pos, corners[1], tmp[0]);
	ml_vector3_sub(pos, corners[2], tmp[1]);
	ml_vector3_cross(tmp[0], tmp[1], camera->viewplanes[3].normal);
	ml_vector3_normalize(camera->viewplanes[3].normal,
		camera->viewplanes[3].normal);
	ml_vector3_sub(pos, corners[2], tmp[0]);
	ml_vector3_sub(pos, corners[3], tmp[1]);
	ml_vector3_cross(tmp[0], tmp[1], camera->viewplanes[4].normal);
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

void	set_camera_viewbox(t_camera *camera, float dims[2],
					t_vec3 forward_up_sideways[3])
{
	t_vec3	dirs[4];
	t_vec3	corners[4];
	t_vec3	screen_origin;
	t_vec3	add;

	ml_vector3_copy(forward_up_sideways[0], camera->viewplanes[0].normal);
	ml_vector3_mul(forward_up_sideways[0],
		ml_vector3_mag(camera->screen.origin), add);
	ml_vector3_add(camera->world_pos, add, screen_origin);
	ml_vector3_mul(forward_up_sideways[1], dims[1], dirs[0]);
	ml_vector3_mul(forward_up_sideways[2], dims[0], dirs[1]);
	ml_vector3_mul(forward_up_sideways[1], -dims[1], dirs[2]);
	ml_vector3_mul(forward_up_sideways[2], -dims[0], dirs[3]);
	ml_vector3_add(screen_origin, dirs[0], corners[0]);
	ml_vector3_add(corners[0], dirs[1], corners[0]);
	ml_vector3_add(screen_origin, dirs[1], corners[1]);
	ml_vector3_add(corners[1], dirs[2], corners[1]);
	ml_vector3_add(screen_origin, dirs[2], corners[2]);
	ml_vector3_add(corners[2], dirs[3], corners[2]);
	ml_vector3_add(screen_origin, dirs[3], corners[3]);
	ml_vector3_add(corners[3], dirs[0], corners[3]);
	set_side_plane_normals(camera, corners, camera->world_pos);
}

/*
** Create new camera
*/

t_camera	*new_camera(void)
{
	t_camera	*camera;

	camera = (t_camera *)ft_calloc(sizeof(t_camera));
	if (!camera)
		return (NULL);
	ml_vector3_set_all(camera->origin, 0);
	return (camera);
}

/*
** Destroy camera
*/

void	scene_cameras_destroy(t_scene *scene)
{
	if (scene->main_camera)
	{
		free(scene->main_camera);
		scene->main_camera = NULL;
	}
	if (scene->third_person_camera)
	{
		free(scene->third_person_camera);
		scene->third_person_camera = NULL;
	}
}
