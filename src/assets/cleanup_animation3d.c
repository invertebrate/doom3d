/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_animation3d.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 15:34:05 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/15 21:07:30 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	animations_3d_destroy(t_assets *assets)
{
	t_3d_object	*model;
	int32_t		i;

	i = -1;
	while (++i < (int32_t)assets->asset_files.num_animation_frames_3d)
	{
		model = hash_map_get(assets->animation_3d_frames,
				(int64_t)assets->asset_files.animation_3d_files[i]);
		if (model)
			l3d_3d_object_destroy(model);
		free((void *)assets->asset_files.animation_3d_files[i]);
	}
	hash_map_destroy(assets->animation_3d_frames);
}
