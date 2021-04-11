/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/07 01:10:31 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static t_bool	object_too_far(t_doom3d *app, t_3d_object *obj)
{
	float		too_far;
	t_vec3		player_to_obj;

	if (app->active_scene->scene_id == scene_id_main_game)
		too_far = app->unit_size * GAME_VIEW_DIST_UNITS;
	else
		too_far = app->unit_size * EDITOR_VIEW_DIST_UNITS;
	ml_vector3_sub(obj->position, app->player.pos,
		player_to_obj);
	if (ml_vector3_mag(player_to_obj) > too_far)
		return (true);
	return (false);
}

static void		add_temp_object_render_triangles(t_doom3d *app,
					t_tri_vec **render_triangles)
{
	t_temp_object 			*tmp;
	t_temp_objects			*node;
	t_triangle				*triangle;
	t_triangle				r_triangle;
	t_vertex				vtc[3];
	int32_t					i;
	
	node = app->active_scene->temp_objects;
	while (node)
	{
		tmp = node->content;
		if (!object_too_far(app, tmp->obj) &&
			object_inside_viewbox(app, tmp->obj))
		{
			i = -1;
			while (++i < tmp->obj->num_triangles)
			{
				triangle = tmp->obj->triangles + i;
				if (triangle_too_far(app, triangle) ||
					!triangle_inside_viewbox(app, triangle))
					continue ;
				prepare_render_triangle(app, &r_triangle, triangle, vtc);
				if (is_rendered(app, &r_triangle))
					clip_and_add_to_render_triangles(app,
						render_triangles, &r_triangle);
			}
		}
		node = node->next;
	}
}

/*
** The checks inside this function optimize the amount of triangles
** prepared for rendering.
*/

static void		add_objects_render_triangles(t_doom3d *app,
					t_tri_vec **render_triangles)
{
	int32_t					i;
	int32_t					j;
	t_triangle				*triangle;
	t_triangle				r_triangle;
	t_vertex				vtc[3];
	
	triangle = &r_triangle;
	i = -1;
	while (++i < (int32_t)(app->active_scene->num_objects +
		app->active_scene->num_deleted))
	{
		if ((app->active_scene->objects[i] == NULL) ||
			object_too_far(app, app->active_scene->objects[i]) ||
			!object_inside_viewbox(app, app->active_scene->objects[i]))
			{
				continue ;
			}
		j = -1;
		while (++j < app->active_scene->objects[i]->num_triangles)
		{
			if (app->active_scene->scene_id != scene_id_editor3d &&
				app->active_scene->objects[i]->type == object_type_npc &&
				((t_npc*)app->active_scene->objects[i]->params)->animation_3d != NULL)
			//^this could be more elegant as in to take into account multiple types
			{
				error_check(((t_npc*)app->active_scene->objects[i]->params)->
							animation_3d->current_object->num_triangles !=
								app->active_scene->objects[i]->num_triangles,
								"Frame object triangle count different from "
								"base object triangle count!");
				triangle = ((t_npc*)app->active_scene->objects[i]->params)->
							animation_3d->current_object->triangles + j;
			}
			else
			{
				triangle = app->active_scene->objects[i]->triangles + j;
			}
			if (triangle_too_far(app, triangle)	 ||
				!triangle_inside_viewbox(app, triangle))
				continue ;
			prepare_render_triangle(app, &r_triangle, triangle, vtc);
			if (is_rendered(app, &r_triangle))
				clip_and_add_to_render_triangles(app,
					render_triangles, &r_triangle);
		}
	}

	add_temp_object_render_triangles(app, render_triangles);
}

static void		add_skybox_render_triangles(t_doom3d *app,
					t_tri_vec **render_triangles)
{
	int					i;
	int					j;
	t_triangle			r_triangle;
	t_vertex			vtc[3];

	i = -1;
	while (++i < 6 && app->active_scene->skybox[i])
	{
		j = -1;
		while (++j < app->active_scene->skybox[i]->num_triangles)
		{
			prepare_skybox_render_triangle(app, &r_triangle,
				app->active_scene->skybox[i]->triangles + j, vtc);
			if (is_rendered(app, &r_triangle))
				clip_and_add_to_render_triangles(app,
					render_triangles, &r_triangle);
		}
	}
}

void			destroy_render_triangle_vecs(t_tri_vec **render_triangles)
{
	l3d_triangle_vec_delete(render_triangles[0]);
	l3d_triangle_vec_delete(render_triangles[1]);
	free(render_triangles);
}

static t_box3d	origo_centered_world_box(t_doom3d *app)
{
	t_box3d				centered_world;
	int32_t				i;

	ft_memcpy(&centered_world,
		&app->active_scene->triangle_tree->root->bounding_box,
		sizeof(t_box3d));
	i = -1;
	while (++i < 3)
	{
		centered_world.xyz_min[i] -= centered_world.center[i];
		centered_world.xyz_max[i] -= centered_world.center[i];
	}
	ml_vector3_copy(centered_world.center, (t_vec3){0, 0, 0});
	return (centered_world);
}

/*
** Sorts all but skybox triangles to be ordered by z depth relative to
** world box (will speed up depth testing and allow transparent rendering)
** render_triangles[0] = normal triangles,
** render_triangles[1] = transparent ones
** offsets render triangles by skybox triangles and reverts back after sort
*/

static void		sort_render_triangles_by_depth(t_doom3d *app,
					t_tri_vec **render_triangles,
					int32_t skybox_offset)
{
	t_box3d				centered_world;
	t_bool				is_skybox_offset;

	centered_world = origo_centered_world_box(app);
	is_skybox_offset = app->active_scene->scene_id != scene_id_editor3d;
	if (is_skybox_offset)
	{
		render_triangles[0]->triangles =
			render_triangles[0]->triangles + skybox_offset;
		render_triangles[0]->size =
			render_triangles[0]->size - skybox_offset;
	}
	triangle_sort_by_depth(render_triangles[0], app->thread_pool,
		&centered_world);
	if (is_skybox_offset)
	{
		render_triangles[0]->triangles =
			render_triangles[0]->triangles - skybox_offset;
		render_triangles[0]->size =
			render_triangles[0]->size + skybox_offset;
	}
	if (render_triangles[1]->size > 0)
		triangle_sort_by_depth(render_triangles[1], app->thread_pool,
			&centered_world);
}

/*
** Prepares triangles for parallel rendering.
** but ignore skybox.
** Sort triangles in z order curve inside world box to speed up render &
** allow transparent render in proper order
*/

t_tri_vec		**prepare_render_triangles(t_doom3d *app)
{
	t_tri_vec			**render_triangles;
	uint32_t			initial_transp_cap;
	int32_t				skybox_offset;

	reset_render_triangle_pool(app);
	initial_transp_cap = 512;
	error_check(!(render_triangles = ft_calloc(sizeof(*render_triangles) * 2)),
		"Failed to allocate render triangle vector pointers");
	render_triangles[0] =
		l3d_triangle_vec_with_capacity(app->active_scene->num_triangles + 12);
	render_triangles[1] =
		l3d_triangle_vec_with_capacity(initial_transp_cap);
	if (app->active_scene->scene_id != scene_id_editor3d)
		add_skybox_render_triangles(app, render_triangles);
	skybox_offset = render_triangles[0]->size;
	add_objects_render_triangles(app, render_triangles);
	sort_render_triangles_by_depth(app, render_triangles, skybox_offset);
	return (render_triangles);
}
