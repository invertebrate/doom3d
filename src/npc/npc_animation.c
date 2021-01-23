/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_animation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 18:41:09 by veilo             #+#    #+#             */
/*   Updated: 2021/01/23 17:56:18 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** NPC type specific function, each type has their own
*/
static void		npc_default_anim_metadata_set(t_anim_metadata *anim_data)
{
	int32_t		i;

	anim_data->frame_count = 6;
	anim_data->anim_count = 1;
	i = -1;
	while (++i < (int32_t)anim_data->frame_count)
		anim_data->scene_frame_key_indices[i] = i;
	ft_memset(anim_data->anim_frame_numbers,
		0, sizeof(uint32_t) * ANIM_3D_MAX_COUNT);
}

static void		npc_anim_frames_set(t_doom3d *app, t_npc *npc)//static
{
	int32_t		i;

	i = -1;
	while(++i < (int32_t)npc->animation->frame_count)
	{
		npc->animation->animation_frames[i] = l3d_object_instantiate(
			hash_map_get(app->active_scene->model_anim_frames,
						(int64_t)npc->anim_frames_keys[i]), app->unit_size);
		npc->animation->animation_frames[i]->material->texture =
			npc->animation->base_object->material->texture;
		npc->animation->animation_frames[i]->material->normal_map =
			npc->animation->base_object->material->normal_map;
		npc->animation->animation_frames[i]->material->shading_opts =
			npc->animation->base_object->material->shading_opts;
		//Todo memcopy light sources... or sth.
	}
}

static void		npc_animation_data_copy(t_npc *npc, t_anim_metadata *anim_data)//static
{
	int32_t		i;

	i = -1;
	npc->animation->frame_count = anim_data->frame_count;
	while (++i < (int)anim_data->anim_count)
	{
		npc->animation->anim_frame_numbers[i] =
			anim_data->anim_frame_numbers[i];
	}
	npc->animation->anim_count = anim_data->anim_count;
}

static void		npc_animation_set(t_doom3d *app, t_npc *npc, t_3d_object *obj,
								t_anim_metadata *anim_data)
{
	int32_t		i;

	i = -1;
	error_check(!(npc->animation = (t_animation*)ft_calloc(sizeof(t_animation))),
		"Failed to malloc for npc animation in npc_animation_set.");
	npc_animation_data_copy(npc, anim_data);
	ft_printf("framecount in malloc: %d\n", npc->animation->frame_count);

	while (++i < (int)npc->animation->frame_count)
	{ 
		// Anim adata defines which key indices are to be called for this npc's
		// frame keys. And since the keys for hash map must be the same pointers
		// we fetch those pointers from active scene's model_animation files
		// Now we can set animation frame keys :)
		npc->anim_frames_keys[i] =
			app->active_scene->asset_files.model_animation_files[
				anim_data->scene_frame_key_indices[i]];
	}
	ft_printf("i count : %d\n", i);
	npc->animation->base_object = obj;
	npc_anim_frames_set(app, npc);
}

void			npc_animation_init(t_doom3d *app, t_3d_object *obj)
{
	t_anim_metadata	anim_data;
	t_npc			*npc;

	npc = (t_npc*)obj->params;
	if (npc->type == npc_type_default)
	{
		npc_default_anim_metadata_set(&anim_data);
	}
	npc_animation_set(app, npc, obj, &anim_data);
}
