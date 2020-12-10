/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_ray_hit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:22:07 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/06 17:59:04 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

/*
** A tradeoff with readability & 42 norms. I refuse to set temp structs for just
** this function, because it'll only bloat the header files. In this case
** bundled arrays are better to beautify the api of triangle_ray_hit function.
*/

static t_bool	l3d_determine_triangle_hit(t_vec3 hsq[3],
				t_triangle *triangle, t_ray *ray, t_hits **hits)
{
	float	afuvt[5];

	afuvt[0] = ml_vector3_dot(triangle->ab, hsq[0]);
	if (afuvt[0] > -L3D_EPSILON && afuvt[0] < L3D_EPSILON)
		return (false);
	afuvt[1] = 1.0 / afuvt[0];
	ml_vector3_sub(ray->origin, triangle->vtc[0]->pos, hsq[1]);
	afuvt[2] = afuvt[1] * ml_vector3_dot(hsq[1], hsq[0]);
	if (afuvt[2] < 0.0 || afuvt[2] > 1.0)
		return (false);
	ml_vector3_cross(hsq[1], triangle->ab, hsq[2]);
	afuvt[3] = afuvt[1] * ml_vector3_dot(ray->dir, hsq[2]);
	if (afuvt[3] < 0.0 || afuvt[2] + afuvt[3] > 1.0)
		return (false);
	afuvt[4] = afuvt[1] * ml_vector3_dot(triangle->ac, hsq[2]);
	if (afuvt[4] > L3D_EPSILON)
	{
		l3d_triangle_hit_record_set(afuvt, ray, triangle, hits);
		return (true);
	}
	return (false);
}

/*
** https://en.wikipedia.org/wiki/Möller–Trumbore_intersection_algorithm
** Returns true if ray hits triangle. A single sidedness test is tested first
** (back-face culling). False is returned if triangle is single sided.
** Hit distance is saved to hit record hit->t.
*/

t_bool			l3d_triangle_ray_hit(t_triangle *triangle, t_ray *ray,
				t_hits **hits)
{
	t_vec3	hsq[3];

	ml_vector3_cross(ray->dir, triangle->ac, hsq[0]);
	return (l3d_determine_triangle_hit(hsq, triangle, ray, hits));
}

/*
** Loop through all triangles under a kd tree node and save the last triangle's
** hit position to hit record.
** !ToDo: Update this function to save multiple hits to the record, though
** kd tree partition ensures they are rare, they are possible when e.g.
** triangles materials are see-through.
*/

static t_bool	l3d_kd_triangles_hit(t_kd_node *node, t_ray *ray,
					t_hits **hits)
{
	t_bool	hit_triangle;
	int		i;

	hit_triangle = false;
	i = -1;
	while (++i < (int)node->triangles->size)
	{
		if (l3d_triangle_ray_hit(node->triangles->triangles[i], ray, hits))
			hit_triangle = true;
	}
	return (hit_triangle);
}

static t_bool	l3d_kd_tree_ray_hit_recursive(t_kd_node *node, t_ray *ray,
					t_hits **hits)
{
	t_bool	hits_right;
	t_bool	hits_left;

	if (l3d_bounding_box_ray_hit(&node->bounding_box, ray, hits))
	{
		if (node->left || node->right)
		{
			hits_left = l3d_kd_tree_ray_hit_recursive(node->left, ray, hits);
			hits_right = l3d_kd_tree_ray_hit_recursive(node->right, ray, hits);
			return (hits_left || hits_right);
		}
		return (l3d_kd_triangles_hit(node, ray, hits));
	}
	return (false);
}

/*
** Test if outer bounding box is hit on kd tree node and binary search further
** until there are no nodes left nor right. On the final node, test triangle
** hits.
*/

t_bool			l3d_kd_tree_ray_hits(t_kd_tree *triangle_tree,
					t_vec3 origin, t_vec3 dir, t_hits **hits)
{
	t_ray			ray;

	*hits = NULL;
	l3d_ray_set(dir, origin, &ray);
	return (l3d_kd_tree_ray_hit_recursive(triangle_tree->root, &ray, hits));
}
