/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:35:42 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/11 17:43:40 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void		set_shotgun_default_anim(t_doom3d *app, t_sprite_anim *anim)
{
	anim->source = hash_map_get(app->active_scene->textures,
		(int64_t)"assets/textures/shotgun_animation.bmp");
	anim->current_frame = 0;
	anim->frame_width = 480;
	anim->frame_height = 528;
	anim->num_frames = 1;
	anim->num_frames_show = 1;
	anim->frames[0] = 0;
}

static void		set_shotgun_reload_anim(t_doom3d *app, t_sprite_anim *anim)
{
	anim->source = hash_map_get(app->active_scene->textures,
		(int64_t)"assets/textures/shotgun_animation.bmp");
	anim->current_frame = 0;
	anim->frame_width = 480;
	anim->frame_height = 528;
	anim->num_frames = 3;
	anim->num_frames_show = 5;
	anim->frames[0] = 4;
	anim->frames[1] = 5;
	anim->frames[2] = 6;
}

static void		set_shotgun_shoot_anim(t_doom3d *app, t_sprite_anim *anim)
{
	anim->source = hash_map_get(app->active_scene->textures,
		(int64_t)"assets/textures/shotgun_animation.bmp");
	anim->current_frame = 0;
	anim->frame_width = 480;
	anim->frame_height = 528;
	anim->num_frames = 3;
	anim->num_frames_show = 3;
	anim->frames[0] = 1;
	anim->frames[1] = 2;
	anim->frames[1] = 3;
}

void	set_player_animations(t_doom3d *app)
{
	set_shotgun_default_anim(app, &app->animations[anim_shotgun_default]);
	set_shotgun_reload_anim(app, &app->animations[anim_shotgun_reload]);
	set_shotgun_shoot_anim(app, &app->animations[anim_shotgun_shoot]);
}