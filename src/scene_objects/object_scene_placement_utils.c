/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_scene_placement_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 17:23:34 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/15 22:22:23 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	set_temp_object_sprite_texture(t_doom3d *app,
					t_3d_object *obj,
					const char *texture_str)
{
	t_surface	*texture;

	texture = hash_map_get(app->assets.sprite_textures,
			(int64_t)texture_str);
	obj->material->texture = texture;
	if (texture != NULL)
		hash_map_add(app->active_scene->object_textures,
			obj->id, (void*)texture_str);
}
