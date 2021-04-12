/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/12 18:04:35 by ohakola          ###   ########.fr       */
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

	ml_vector3_normalize(collision_normal, collision_normal);
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

static void		rays_from_collider(t_player *future_player,
					t_ray rays[32])
{
	// Corner xyz min
	l3d_ray_set((t_vec3){-X_DIR, 0, 0}, (t_vec3){future_player->aabb.xyz_min[0],
		future_player->aabb.xyz_min[1], future_player->aabb.xyz_min[2]}, &rays[0]);
	l3d_ray_set((t_vec3){0, Y_DIR, 0}, (t_vec3){future_player->aabb.xyz_min[0],
		future_player->aabb.xyz_min[1], future_player->aabb.xyz_min[2]}, &rays[1]);
	l3d_ray_set((t_vec3){0, 0, -Z_DIR}, (t_vec3){future_player->aabb.xyz_min[0],
		future_player->aabb.xyz_min[1], future_player->aabb.xyz_min[2]}, &rays[2]);
	// Corner xy min zmax
	l3d_ray_set((t_vec3){-X_DIR, 0, 0}, (t_vec3){future_player->aabb.xyz_min[0],
		future_player->aabb.xyz_min[1], future_player->aabb.xyz_max[2]}, &rays[3]);
	l3d_ray_set((t_vec3){0, Y_DIR, 0}, (t_vec3){future_player->aabb.xyz_min[0],
		future_player->aabb.xyz_min[1], future_player->aabb.xyz_max[2]}, &rays[4]);
	l3d_ray_set((t_vec3){0, 0, Z_DIR}, (t_vec3){future_player->aabb.xyz_min[0],
		future_player->aabb.xyz_min[1], future_player->aabb.xyz_max[2]}, &rays[5]);
	// Corner y min xz max
	l3d_ray_set((t_vec3){X_DIR, 0, 0}, (t_vec3){future_player->aabb.xyz_max[0],
		future_player->aabb.xyz_min[1], future_player->aabb.xyz_max[2]}, &rays[6]);
	l3d_ray_set((t_vec3){0, Y_DIR, 0}, (t_vec3){future_player->aabb.xyz_max[0],
		future_player->aabb.xyz_min[1], future_player->aabb.xyz_max[2]}, &rays[7]);
	l3d_ray_set((t_vec3){0, 0, Z_DIR}, (t_vec3){future_player->aabb.xyz_max[0],
		future_player->aabb.xyz_min[1], future_player->aabb.xyz_max[2]}, &rays[8]);
	// Corner yz min x max
	l3d_ray_set((t_vec3){X_DIR, 0, 0}, (t_vec3){future_player->aabb.xyz_max[0],
		future_player->aabb.xyz_min[1], future_player->aabb.xyz_min[2]}, &rays[9]);
	l3d_ray_set((t_vec3){0, Y_DIR, 0}, (t_vec3){future_player->aabb.xyz_max[0],
		future_player->aabb.xyz_min[1], future_player->aabb.xyz_min[2]}, &rays[10]);
	l3d_ray_set((t_vec3){0, 0, -Z_DIR}, (t_vec3){future_player->aabb.xyz_max[0],
		future_player->aabb.xyz_min[1], future_player->aabb.xyz_min[2]}, &rays[11]);
	// SAME FOR BOTTOM CORNERS (y max)
	l3d_ray_set((t_vec3){-X_DIR, 0, 0}, (t_vec3){future_player->aabb.xyz_min[0],
		future_player->aabb.xyz_max[1], future_player->aabb.xyz_min[2]}, &rays[12]);
	l3d_ray_set((t_vec3){0, -Y_DIR, 0}, (t_vec3){future_player->aabb.xyz_min[0],
		future_player->aabb.xyz_max[1], future_player->aabb.xyz_min[2]}, &rays[13]);
	l3d_ray_set((t_vec3){0, 0, -Z_DIR}, (t_vec3){future_player->aabb.xyz_min[0],
		future_player->aabb.xyz_max[1], future_player->aabb.xyz_min[2]}, &rays[14]);

	l3d_ray_set((t_vec3){-X_DIR, 0, 0}, (t_vec3){future_player->aabb.xyz_min[0],
		future_player->aabb.xyz_max[1], future_player->aabb.xyz_max[2]}, &rays[15]);
	l3d_ray_set((t_vec3){0, -Y_DIR, 0}, (t_vec3){future_player->aabb.xyz_min[0],
		future_player->aabb.xyz_max[1], future_player->aabb.xyz_max[2]}, &rays[16]);
	l3d_ray_set((t_vec3){0, 0, Z_DIR}, (t_vec3){future_player->aabb.xyz_min[0],
		future_player->aabb.xyz_max[1], future_player->aabb.xyz_max[2]}, &rays[17]);

	l3d_ray_set((t_vec3){X_DIR, 0, 0}, (t_vec3){future_player->aabb.xyz_max[0],
		future_player->aabb.xyz_max[1], future_player->aabb.xyz_max[2]}, &rays[18]);
	l3d_ray_set((t_vec3){0, -Y_DIR, 0}, (t_vec3){future_player->aabb.xyz_max[0],
		future_player->aabb.xyz_max[1], future_player->aabb.xyz_max[2]}, &rays[19]);
	l3d_ray_set((t_vec3){0, 0, Z_DIR}, (t_vec3){future_player->aabb.xyz_max[0],
		future_player->aabb.xyz_max[1], future_player->aabb.xyz_max[2]}, &rays[20]);
		
	l3d_ray_set((t_vec3){X_DIR, 0, 0}, (t_vec3){future_player->aabb.xyz_max[0],
		future_player->aabb.xyz_max[1], future_player->aabb.xyz_min[2]}, &rays[21]);
	l3d_ray_set((t_vec3){0, -Y_DIR, 0}, (t_vec3){future_player->aabb.xyz_max[0],
		future_player->aabb.xyz_max[1], future_player->aabb.xyz_min[2]}, &rays[22]);
	l3d_ray_set((t_vec3){0, 0, -Z_DIR}, (t_vec3){future_player->aabb.xyz_max[0],
		future_player->aabb.xyz_max[1], future_player->aabb.xyz_min[2]}, &rays[23]);

	// SAME FOR middle part of aabb
	l3d_ray_set((t_vec3){-X_DIR, 0, 0}, (t_vec3){future_player->aabb.xyz_min[0],
		future_player->pos[1], future_player->aabb.xyz_min[2]}, &rays[24]);
	l3d_ray_set((t_vec3){0, 0, -Z_DIR}, (t_vec3){future_player->aabb.xyz_min[0],
		future_player->pos[1], future_player->aabb.xyz_min[2]}, &rays[25]);

	l3d_ray_set((t_vec3){-X_DIR, 0, 0}, (t_vec3){future_player->aabb.xyz_min[0],
		future_player->pos[1], future_player->aabb.xyz_max[2]}, &rays[26]);
	l3d_ray_set((t_vec3){0, 0, Z_DIR}, (t_vec3){future_player->aabb.xyz_min[0],
		future_player->pos[1], future_player->aabb.xyz_max[2]}, &rays[27]);

	l3d_ray_set((t_vec3){X_DIR, 0, 0}, (t_vec3){future_player->aabb.xyz_max[0],
		future_player->pos[1], future_player->aabb.xyz_max[2]}, &rays[28]);
	l3d_ray_set((t_vec3){0, 0, Z_DIR}, (t_vec3){future_player->aabb.xyz_max[0],
		future_player->pos[1], future_player->aabb.xyz_max[2]}, &rays[29]);
		
	l3d_ray_set((t_vec3){X_DIR, 0, 0}, (t_vec3){future_player->aabb.xyz_max[0],
		future_player->pos[1], future_player->aabb.xyz_min[2]}, &rays[30]);
	l3d_ray_set((t_vec3){0, 0, -Z_DIR}, (t_vec3){future_player->aabb.xyz_max[0],
		future_player->pos[1], future_player->aabb.xyz_min[2]}, &rays[31]);
}

/*
** Direct rays from bounding box corners and middle between corners
** See if they hit & subtract movement add so we limit the movement by the hit
** triangles.
*/

void			collision_limit_player(t_doom3d *app, t_vec3 add)
{
	int32_t		i;
	t_player	future_player;
	t_hits		*hits;
	t_hit		*closest_triangle_hit;
	t_ray		rays[32];

	set_future_player(app, add, &future_player);
	rays_from_collider(&future_player, rays);
	i = -1;
	while (++i < 32)
	{
		hits = NULL;
		if (l3d_kd_tree_ray_hits(app->active_scene->triangle_tree, rays[i].origin,
			rays[i].dir, &hits))
		{
			closest_triangle_hit = NULL;
			l3d_get_closest_triangle_hit_at_range(hits,
				&closest_triangle_hit, -1,
				0.1 * app->unit_size);
			if (closest_triangle_hit != NULL)
			{
				LOG_TRACE("Hit and close enough %d", i);
				limit_movement_add_by_collision(closest_triangle_hit->normal,
					add);
				l3d_delete_hits(&hits);
				return ;
			}
			l3d_delete_hits(&hits);
		}
	}
}
