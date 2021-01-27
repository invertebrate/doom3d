/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veilo <veilo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 18:41:09 by veilo             #+#    #+#             */
/*   Updated: 2020/12/30 20:32:36 by veilo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** NPC type specific function, each type has their own
*/
void		npc_default_anim_metadata_set(t_anim_metadata *anim_data)
{
	anim_data->frame_count = 6;
	anim_data->anim_count = 1;
	anim_data->frames_start_idx = 0;
	ft_memset(anim_data->anim_frame_numbers,
	0, sizeof(uint32_t) * ANIM_3D_FRAME_MAX);
	anim_data->anim_frame_numbers[0] = 0;
}

void			npc_animation_init(t_doom3d *app, t_3d_object *obj)
{
	// ft_printf("anim_init\n");
	t_anim_metadata	anim_data;
	t_npc			*npc;

	npc = (t_npc*)obj->params;
	npc->animation->base_object = obj;//new change
	if (npc->type == npc_type_default)
	{
		npc_default_anim_metadata_set(&anim_data);
	}
		npc_animation_set(app, obj, npc, &anim_data);
}

/*
** Removes the .obj from the end of the string
*/

char			*truncate_model_file_path(const char *file_path)
{
	char	*path;
	int		len;
	int		i;

	i = -1;
	len = ft_strlen(file_path);
	ft_printf("filepath: %s  len: %d\n", file_path, len);
	error_check(!(path = (char*)ft_calloc(sizeof(char) * len)),
		"Failed to malloc for file path in truncate_model_file_path.");
	while (i < len - 4)
	{
		path[i] = file_path[i];
		i++;;
	}
	ft_printf("filepath after truncation: %s\n", path);
	return (path);
}

void			npc_anim_frames_set(t_doom3d *app, t_3d_object *obj, t_npc *npc)//static
{
	int		i;

	i = npc->animation->frames_start_idx - 1;
	while (++i < (int)(npc->animation->frames_start_idx + (npc->animation->frame_count)))
	{
		npc->animation->animation_frames[i] = l3d_object_instantiate(
		hash_map_get(app->active_scene->anim_frames,
			(int64_t)(app->active_scene->asset_files.animation_files[i])), app->unit_size);
		npc->animation->animation_frames[i]->material->shading_opts = obj->material->shading_opts;
		// ft_printf("FRAMES SET shading opts: %d\n", ((t_npc*)obj->params)->animation->animation_frames[i]->material->shading_opts);
		

		//copy shading options or use the parent's in rendering if possible?
	}
}

void			npc_animation_data_copy(t_npc *npc, t_anim_metadata *anim_data)//static
{
	int		i;

	i = -1;
	npc->animation->frame_count = anim_data->frame_count;
	while (++i < (int)anim_data->anim_count)
	{
		npc->animation->anim_frame_numbers[i] =
			anim_data->anim_frame_numbers[i];
	}
	npc->animation->anim_count = anim_data->anim_count;
	npc->animation->frames_start_idx = anim_data->frames_start_idx;
}

void				npc_animation_set(t_doom3d *app, t_3d_object *obj, t_npc *npc,
								t_anim_metadata *anim_data)
{
	error_check(!(npc->animation = (t_animation*)ft_calloc(sizeof(t_animation))),
		"Failed to malloc for npc animation in npc_animation_set.");
	npc_animation_data_copy(npc, anim_data);
	npc_anim_frames_set(app, obj, npc);
}