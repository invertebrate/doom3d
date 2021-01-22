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
	ft_memset(anim_data->anim_frame_numbers,
	0, sizeof(uint32_t) * ANIM_3D_MAX_COUNT);
	anim_data->anim_frame_numbers[0] = 0;
}

void			npc_animation_init(t_doom3d *app, t_3d_object *obj)
{
	// ft_printf("anim_init\n");
	t_anim_metadata	anim_data;
	t_npc			*npc;

	npc = (t_npc*)obj->params;
	if (npc->type == npc_type_default)
	{
		npc_default_anim_metadata_set(&anim_data);
	}
		npc_animation_set(app, npc, &anim_data);
}

/*
** Removes the .obj from the end of the string
*/

static char			*truncate_model_file_path(const char *file_path)
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

void			npc_anim_frames_set(t_doom3d *app, t_npc *npc)//static
{
	int		i;

	i = -1;
	while(++i < (int)npc->animation->frame_count)
	{
		npc->animation->animation_frames[i] =
			hash_map_get(app->active_scene->anim_frames,
						(int64_t)npc->anim_frames_key[i]);
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
		ft_printf("anim frame numbers: %d\n", anim_data->anim_frame_numbers[i]);
	}
	npc->animation->anim_count = anim_data->anim_count;
	ft_printf("anim count: %d\n", npc->animation->anim_count);
}

void			npc_anim_frame_keys_set(t_npc *npc)//static
{
	int		i;

	i = -1;
	while (++i < (int)(npc->animation->frame_count))
	if (i < 10)
	{
		ft_sprintf(npc->anim_frames_key[i], "%s_00%d.obj", truncate_model_file_path(npc->model_key), i);
		ft_printf("anim frame key : %s\n", npc->anim_frames_key[i]);//
	}
	else if (i < 100)
	{
		ft_sprintf(npc->anim_frames_key[i], "%s_0%d.obj", truncate_model_file_path(npc->model_key), i);
		ft_printf("anim frame key : %s\n", npc->anim_frames_key[i]);//
	}
}

void				npc_animation_set(t_doom3d *app, t_npc *npc,
								t_anim_metadata *anim_data)
{
	int		i;

	i = -1;
	error_check(!(npc->animation = (t_animation*)ft_calloc(sizeof(t_animation))),
		"Failed to malloc for npc animation in npc_animation_set.");
	npc_animation_data_copy(npc, anim_data);
	ft_printf("framecount in malloc: %d\n", npc->animation->frame_count);
	error_check(!(npc->anim_frames_key =
		(char**)ft_calloc(sizeof(char*) * npc->animation->frame_count)),
		"Failed to malloc for npc animation frames key array in npc_animation_set.");
	error_check(!(npc->animation->animation_frames =
		(t_3d_object**)ft_calloc(sizeof(t_3d_object*) * npc->animation->frame_count)),
		"Failed to malloc for npc animation frames array npc_animation_set.");
	while (++i < (int)npc->animation->frame_count)
	{ 
		error_check(!(npc->anim_frames_key[i] =
		(char*)ft_calloc(sizeof(char) * (ft_strlen(npc->model_key) + 10))),
		"Failed to malloc for npc animation frames key in npc_animation_set.");
	}
	ft_printf("i count : %d\n", i);

	npc->animation->base_object = (t_3d_object*)hash_map_get(app->active_scene->models,
												(int64_t)npc->model_key);
	npc_anim_frame_keys_set(npc);
	// npc_anim_frames_set(app, npc);

}