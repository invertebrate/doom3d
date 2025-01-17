/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 13:17:37 by ohakola           #+#    #+#             */
/*   Updated: 2021/06/21 17:19:23 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	invisible_trigger_and_path_shading(t_3d_object *obj)
{
	if (obj->params_type == trigger_player_start)
		obj->material->shading_opts
			= e_shading_green | e_shading_transparent | e_shading_lit;
	if (obj->params_type == trigger_player_end)
		obj->material->shading_opts
			= e_shading_red | e_shading_transparent | e_shading_lit;
	if (obj->params_type == trigger_hurtbox)
		obj->material->shading_opts
			= e_shading_yellow | e_shading_transparent | e_shading_lit;
	if (obj->params_type == trigger_jukebox)
		obj->material->shading_opts
			= e_shading_blue | e_shading_transparent | e_shading_lit;
	if (obj->params_type == trigger_musicbox)
		obj->material->shading_opts
			= e_shading_cyan | e_shading_transparent | e_shading_lit;
	if (obj->params_type == object_type_path)
		obj->material->shading_opts
			= e_shading_cyan | e_shading_transparent | e_shading_lit;
}

/*
** Set invisible objects to be visibly highlighted in editor
*/

void	editor_objects_invisible_highlight(t_doom3d *app)
{
	t_3d_object	*obj;
	int32_t		i;

	i = -1;
	while (++i < (int32_t)(app->active_scene->num_objects
		+ app->active_scene->num_free_indices))
	{
		obj = app->active_scene->objects[i];
		if (obj == NULL)
			continue ;
		if (obj->type == object_type_trigger || obj->type == object_type_path)
		{
			obj->material->shading_opts = (obj->material->shading_opts
					& ~(e_shading_invisible));
			invisible_trigger_and_path_shading(obj);
		}
		if (obj->type == object_type_light
			&& obj->params_type != light_type_breakable
			&& obj->params_type != light_type_mushroom)
			obj->material->shading_opts = (obj->material->shading_opts
					& ~(e_shading_invisible));
	}
}

/*
** Set invisible objects to be invisible again
*/

void	editor_objects_invisible_unhighlight(t_doom3d *app)
{
	t_3d_object	*obj;
	int32_t		i;

	i = -1;
	while (++i < (int32_t)(app->active_scene->num_objects
		+ app->active_scene->num_free_indices))
	{
		obj = app->active_scene->objects[i];
		if (obj
			&& ((obj->type == object_type_trigger
					&& (obj->params_type == trigger_player_start
						|| obj->params_type == trigger_player_end
						|| obj->params_type == trigger_hurtbox
						|| obj->params_type == trigger_jukebox
						|| obj->params_type == trigger_musicbox))
				|| obj->type == object_type_path))
			obj->material->shading_opts = e_shading_invisible;
		if (obj && obj->type == object_type_light
			&& obj->params_type != light_type_breakable
			&& obj->params_type != light_type_mushroom)
			obj->material->shading_opts |= e_shading_invisible;
	}
}

/*
** Returns true if mouse is inside editor render view
*/

t_bool	mouse_inside_editor_view(t_doom3d *app)
{
	return (app->mouse.x > app->window->view_3d_pos[0] && app->mouse.x
		< app->window->view_3d_pos[0]
		+ app->window->framebuffer_3d->width
		&& app->mouse.y > app->window->view_3d_pos[1] && app->mouse.y
		< app->window->view_3d_pos[1]
		+ app->window->framebuffer_3d->height);
}
