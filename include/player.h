/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 14:55:49 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/15 15:29:13 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# define NUM_WEAPONS 4
# define NUM_PROJECTILES 4
# define NUM_PLAYER_ANIMATIONS 16
# define PLAYER_SPEED 6.0
# define PLAYER_ROTATION_SPEED 0.2

#include "lib3d.h"
#include "game_objects.h"

/*
** Directions to which player can move
*/

typedef enum				e_move
{
	move_forward,
	move_backward,
	move_strafe_left,
	move_strafe_right,
	move_down,
	move_up,
}							t_move;

/*
** Data defining player functionality and toggles.
*/

typedef struct				s_player
{
	t_vec3					pos;
	t_vec3					forward;
	t_vec3					sideways;
	t_vec3					up;
	t_bool					is_running;
	t_bool					is_shooting;
	t_bool					is_reloading;
	t_bool					is_moving;
	t_bool					is_rotating;
	float					speed;
	float					rot_speed;
	float					rot_x;
	float					rot_y;
	float					player_height;
	float					fire_rate_per_sec;
	t_mat4					rotation;
	t_mat4					inv_rotation;
	t_mat4					translation;
	t_mat4					inv_translation;
	t_box3d					aabb;
	t_weapon				weapons[NUM_WEAPONS];
	t_weapon				*equipped_weapon;
	int						hp;
}							t_player;

/*
** A list of animations that the sprite animation under player hud
** will be able to display.
*/

typedef enum				e_player_animation
{
	anim_none = 0,
	anim_shotgun_default = 1,
	anim_shotgun_shoot = 2,
	anim_shotgun_reload = 3,
	anim_glock_default = 4,
	anim_glock_shoot = 5,
	anim_glock_reload = 6,
}							t_player_animation;

/*
** Data which defines different things that belong to player hud.
** // ToDo: Might be unnecessary, let's see
*/

typedef struct				s_player_hud
{
	t_player_animation		curr_animation;
}							t_player_hud;

#endif