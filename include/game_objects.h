/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_objects.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 14:36:18 by ohakola           #+#    #+#             */
/*   Updated: 2021/02/11 09:56:15 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_OBJECTS_H
# define GAME_OBJECTS_H

# define NPC_DEFAULT_MODEL "assets/models/box.obj"
# define NPC_DEFAULT_TEXTURE "assets/textures/rock.bmp"
# define NPC_DEFAULT_NORMM "assets/textures/rock.bmp"

# include "libgmatrix.h"

# define PATH_NEIGHBOUR_MAX 8
# define MAX_PATROL_NODES 16

/*
** A list defining what kind of objects the doom3d app contains in its scene /
** world. Each object has their own specific functionality, if any :)
** e.g. triggers react when player (or other) hit its bounding box (aabb),
** triggers can also be e.g. weapon drops.
** Default objects are just regular rendered 3d objects.
** t_3d_object 
*/

typedef enum				e_object_type
{
	object_type_default = 0,
	object_type_npc = 1,
	object_type_projectile = 2,
	object_type_trigger = 3,
	object_type_light = 4,
	object_type_path = 5,
}							t_object_type;

/*
** Prefab is a combination of assets, e.g. 3d model + texture + normal map.
** Or later a combination of 3d models and their textures.
** They are a bundle of things placeable by the editor.
*/

typedef enum				e_prefab_type
{
	prefab_plane = 1,
	prefab_path_node= 2,
}							t_prefab_type;

/*
** Game object Params types
** ----------------------------
*/

/*
** Sub (params_type) for object_type_path
*/

typedef struct				s_path_node
{
	t_bool		is_visited;
	int32_t		num_neighbors;
	t_3d_object	*neighbors[PATH_NEIGHBOUR_MAX]; //How many neighbors can have?
	t_3d_object	*parent;
}							t_path_node;

/*
** A list of various trigger types
** t_trigger_type may be used as a sub type (params_type) under t_3d_object
*/

typedef enum				e_trigger_type
{
	trigger_player_start = 1,
	trigger_player_end = 2,
	trigger_weapon_drop_shotgun = 3,
	trigger_weapon_drop_glock = 4,
	trigger_weapon_drop_rpg = 5,
	trigger_item_jetpack,
}							t_trigger_type;

/*
** A list of npc types
** t_npc_type may be used as a sub type (params_type) under t_3d_object
*/

typedef enum				e_npc_type
{
	npc_type_default,
}							t_npc_type;

/*
** A list of different projectiles that are used under weapons
** and also as their specific 3d objects.
** t_projectile_type may be used as a sub type (params_type) under t_3d_object
*/

typedef enum				e_projectile_type
{
	projectile_type_rpg = 0,
	projectile_type_bullet = 1,
	projectile_type_none = 2,
}							t_projectile_type;

/*
** ----------------------------
*/

/*
** Structs and enums defining data that may or may not belong
** inside t_3d_object->params or data that defines other game logic
** ----------------------------
*/

/*
** A list of weapons available for player
** These ids define e.g. which animation for player is used when shooting or
** reloading, or how player shoots in the game world.
*/

typedef enum				e_weapon_id
{
	weapon_fist = 0,
	weapon_glock = 1,
	weapon_shotgun = 2,
	weapon_rpg = 3,
}							t_weapon_id;

/*
** Weapon struct containing relevant data for player's world interaction
** with enemies.
*/

typedef struct				s_weapon
{
	t_weapon_id				id;
	int						ammo;
	float					fire_rate;
	float					range;
	t_projectile_type		projectile;
	int						damage_per_hit;
}							t_weapon;


/*
** Projectile data defining how projectile objects are instantiated 
** and how projectile interacts with the game world.
*/

typedef struct				s_projectile
{
	t_projectile_type		type;
	int						damage;
	float					speed;
	float					range;
	float					traveled;
	float					radius;
	const char				*model_key;
	const char				*texture_key;
	const char				*normal_map_key;
	t_vec3					dir;
	t_vec3					euler_angles;
}							t_projectile;

/*
** Enum defining npc's state.
*/

typedef enum				e_npc_state
{
	state_idle,
	state_attack,
	state_atk_anim,
	state_death_anim,
}							t_npc_state;

/*
** Enum defining npc's attack pattern
*/

typedef enum				e_npc_action
{
	action_wait,
	action_melee_basic,
	action_projectile_rpg,
	action_repeat,
}							t_npc_action;

/*
** NPC data defining how npc behaves in the world & how objects under npc
** are moved in the game world. Also defines how the npc t_3d_object
** gets instantiated.
*/

typedef struct				s_npc
{
	t_bool					is_jumping;
	t_bool					is_falling;
	t_bool					is_grounded;
	t_vec3					dir;
	float					angle;
	float					vision_range;
	int						interest;
	int						max_interest;
	t_bool					advance;
	float					atk_range;
	int						atk_dmg;
	uint32_t				atk_start;
	uint32_t				atk_dur;
	uint32_t				atk_timer;
	int						atk_pattern[128];
	int						atk_pattern_index;
	t_3d_object				*patrol_path[MAX_PATROL_NODES + 1];
	int						patrol_path_index;
	int32_t					num_patrol_path_nodes;
	float					speed;
	float					rot_speed;
	float					dist;
	int						state;
	int						hp;
	int						type;
	t_vec3					velocity;
	const char				*texture_key;
	const char				*model_key;
	const char				*normal_map_key;
}							t_npc;


/*
** ----------------------------
*/

#endif