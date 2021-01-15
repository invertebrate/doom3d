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

static char			*truncate_model_file_path(const char *file_path)
{
	char	*path;
	int		len;

	len = ft_strlen(file_path);
	error_check(!(path = (char*)ft_calloc(sizeof(len))),
		"Failed to malloc for file path in truncate_model_file_path.");
	while (len - 3 > 0)
	{
		path[len] = file_path[len];
		len--;
	}
	return (path);
}

static t_3d_object	**npc_anim_frames_set(t_doom3d *app, t_npc *npc)
{
	int		i;

	i = -1;
	while(++i < (int)npc->animation->frame_count)
	{
		npc->animation->animation_frames[i] =
			hash_map_get(app->active_scene->anim_frames,
						(int64_t)npc->anim_frames_key[i]);
	}
	return (NULL);//figure out the return and the pointer array thingy
}

static void	npc_animation_data_copy(t_npc *npc, t_anim_metadata *anim_data)
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
}

static void	npc_anim_frame_keys_set(t_npc *npc)
{
	int		i;

	i = -1;
	while (++i < (int)(npc->animation->frame_count))
	if (i < 10)
	{
		ft_sprintf(npc->anim_frames_key[i], "%s_00", truncate_model_file_path(npc->model_key));
		ft_printf("anim frame key : %s\n", npc->anim_frames_key[i]);//
	}
	else if (i < 100)
	{
		ft_sprintf(npc->anim_frames_key[i], "%s_0", truncate_model_file_path(npc->model_key));
		ft_printf("anim frame key : %s\n", npc->anim_frames_key[i]);//
	}
}

void		npc_animation_set(t_doom3d *app, t_npc *npc,
								t_anim_metadata *anim_data)
{
	if (npc->animation != NULL)
	{
		free(npc->animation);
		npc->animation = NULL;
	}
	error_check(!(npc->animation = (t_animation*)ft_calloc(sizeof(t_animation))),
		"Failed to malloc for npc animation in npc_animation_set.");
	error_check(!(npc->anim_frames_key =
		(char**)ft_calloc(sizeof(char*) * npc->animation->frame_count)),
		"Failed to malloc for npc animation in npc_animation_set.");
	npc_animation_data_copy(npc, anim_data);
	npc->animation->base_object = hash_map_get(app->active_scene->models,
												(int64_t)npc->model_key);
	npc_anim_frame_keys_set(npc);
	npc->animation->animation_frames = npc_anim_frames_set(app, npc);
}