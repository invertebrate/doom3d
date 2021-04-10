/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/10 14:27:04 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** https://gamedev.stackexchange.com/questions/49956/
** collision-detection-smooth-wall-sliding-no-bounce-effect
*/

static void		limit_movement_add_by_collision(t_vec3 collision_normal,
					t_vec3 dir_add)
{
	t_vec3		direction_wall_part;

	ml_vector3_mul(collision_normal,
		ml_vector3_dot(dir_add, collision_normal), direction_wall_part);
	if (direction_wall_part[1] > 0)
		direction_wall_part[1] = 0;
	ml_vector3_sub(dir_add, direction_wall_part, dir_add);
}

static void		set_future_player(t_doom3d *app, t_vec3 add,
					t_player *future_player)
{
	t_vec3	new_add;

	ml_vector3_add(add, 
			(t_vec3) {0, -app->player.player_height / 4, 0}, new_add);
	ft_memcpy(future_player, &app->player, sizeof(t_player));
	ml_vector3_add(future_player->pos, new_add, future_player->pos);
	player_update_aabb(future_player);
}

void			collision_limit_player(t_doom3d *app, t_vec3 add)
{
	int32_t		i;
	t_3d_object	*obj;
	t_player	future_player;
	t_vec3		diff;
	t_hit		*hit;

	set_future_player(app, add, &future_player);
	i = -1;
	while (++i < (int32_t)(app->active_scene->num_objects +
		app->active_scene->num_deleted))
	{
		obj = app->active_scene->objects[i];
		if (obj == NULL)
			continue ;
		ml_vector3_sub(obj->position, future_player.pos, diff);
		if (ml_vector3_mag(diff) > app->unit_size * 10 || obj->type == object_type_trigger || obj->type == object_type_path)
			continue ;
		if (l3d_aabb_collides(&obj->aabb, &future_player.aabb))
		{
			hit = l3d_get_aabb_hit_record(&future_player.aabb, &obj->aabb);
			if (hit != NULL)
			{
				if (!obj->aabb.is_collider)
					limit_movement_add_by_collision(hit->normal, add);
				free(hit);
			}
		}
	}
}
