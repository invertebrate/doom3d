/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_animations1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:35:42 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/25 12:41:23 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** This function is called when player animation is to be switched to
** shoot animation
*/

void	set_player_shoot_frame(t_doom3d *app)
{
	if (app->player.equipped_weapon->id == weapon_shotgun)
		set_player_animation(app, anim_shotgun_shoot);
	else if (app->player.equipped_weapon->id == weapon_pistol)
		set_player_animation(app, anim_pistol_shoot);
	else if (app->player.equipped_weapon->id == weapon_fist)
		set_player_animation(app, anim_fist_shoot);
	else if (app->player.equipped_weapon->id == weapon_rpg)
		set_player_animation(app, anim_rpg_shoot);
	if (app->settings.is_debug)
		LOG_DEBUG("Set player shoot sprite frame");
}

/*
** This function is called when player animation is to be switched to
** default animation
*/

void	set_player_default_frame(t_doom3d *app)
{
	if (app->player.equipped_weapon->id == weapon_shotgun)
		set_player_animation(app, anim_shotgun_default);
	else if (app->player.equipped_weapon->id == weapon_pistol)
		set_player_animation(app, anim_pistol_default);
	else if (app->player.equipped_weapon->id == weapon_fist)
		set_player_animation(app, anim_fist_default);
	else if (app->player.equipped_weapon->id == weapon_rpg)
	{
		if (app->player.equipped_weapon->clip == 0)
			set_player_animation(app, anim_rpg_special);
		else
			set_player_animation(app, anim_rpg_default);
	}
}

/*
** This function is called when player animation is to be switched to
** reload animation
*/

void	set_player_reload_frame(t_doom3d *app)
{
	if (app->player.equipped_weapon->id == weapon_shotgun)
		set_player_animation(app, anim_shotgun_reload);
	else if (app->player.equipped_weapon->id == weapon_pistol)
		set_player_animation(app, anim_pistol_reload);
	else if (app->player.equipped_weapon->id == weapon_fist)
		set_player_animation(app, anim_fist_reload);
	else if (app->player.equipped_weapon->id == weapon_rpg)
		set_player_animation(app, anim_rpg_reload);
	if (app->settings.is_debug)
		LOG_DEBUG("Set player reload sprite frame");
}

t_player_anim_state	player_animation_state(t_doom3d *app)
{
	int	current;

	current = app->player_hud.curr_animation;
	if (current == anim_shotgun_default
		|| current == anim_pistol_default
		|| current == anim_shotgun_default
		|| current == anim_rpg_default
		|| current == anim_rpg_special
		|| current == anim_fist_default)
		return (anim_state_default);
	else if (current == anim_shotgun_shoot
		|| current == anim_pistol_shoot
		|| current == anim_shotgun_shoot
		|| current == anim_rpg_shoot
		|| current == anim_fist_shoot)
		return (anim_state_shoot);
	else if (current == anim_shotgun_reload
		|| current == anim_pistol_reload
		|| current == anim_shotgun_reload
		|| current == anim_rpg_reload)
		return (anim_state_reload);
	return (0);
}

/*
** Moves on animation frames if they should be moved on. If An animation frame
** is finished, the frames don't get incremented. Frame time left is decreased
** by delta time until it's <= 0. Current frame moves to next. Once last
** frame is reached, animation is set to be finished.
*/

void	player_animation_update(t_doom3d *app)
{
	t_sprite_anim	*curr_player_anim;

	curr_player_anim = &app->animations[app->player_hud.curr_animation];
	if (app->active_scene->scene_id != scene_id_main_game
		|| curr_player_anim->is_finished)
		return ;
	curr_player_anim->frame_time_left -= app->info.delta_time;
	if (curr_player_anim->frame_time_left <= 0)
	{
		curr_player_anim->frame_time_left = 0;
		curr_player_anim->current_frame++;
		curr_player_anim->frame_time_left
			= curr_player_anim->frame_time;
		if (curr_player_anim->current_frame >= curr_player_anim->num_frames)
		{
			curr_player_anim->is_finished = true;
			curr_player_anim->current_frame = 0;
		}
	}
}
