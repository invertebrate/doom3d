/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 13:17:37 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/06 13:22:43 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	invisible_shading_tone(t_3d_object *obj)
{
	if (obj->params_type == trigger_player_start)
		obj->material->shading_opts
			= e_shading_green | e_shading_transparent;
	if (obj->params_type == trigger_player_end)
		obj->material->shading_opts
			= e_shading_red | e_shading_transparent;
	if (obj->params_type == trigger_hurtbox)
		obj->material->shading_opts
			= e_shading_yellow | e_shading_transparent;
	if (obj->params_type == trigger_jukebox)
		obj->material->shading_opts
			= e_shading_blue | e_shading_transparent;
	if (obj->params_type == object_type_path)
		obj->material->shading_opts
			= e_shading_cyan | e_shading_transparent;
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
		+ app->active_scene->num_deleted))
	{
		obj = app->active_scene->objects[i];
		if (obj == NULL)
			continue ;
		if (obj->type == object_type_trigger || obj->type == object_type_path)
		{
			obj->material->shading_opts = (obj->material->shading_opts
					& ~(e_shading_invisible));
			invisible_shading_tone(obj);
		}
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
		+ app->active_scene->num_deleted))
	{
		obj = app->active_scene->objects[i];
		if (obj
			&& ((obj->type == object_type_trigger
					&& (obj->params_type == trigger_player_start
						|| obj->params_type == trigger_player_end
						|| obj->params_type == trigger_hurtbox
						|| obj->params_type == trigger_jukebox))
				|| obj->type == object_type_path))
			obj->material->shading_opts = e_shading_invisible;
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
