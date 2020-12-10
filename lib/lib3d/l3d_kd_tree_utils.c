/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_kd_tree_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:22:07 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/06 17:22:51 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

/*
** Pushes triangles into left or right depending ont heir
** mid point at given axis (longes).
*/

void				l3d_kd_tree_split_triangles(t_tri_vec *triangles,
					t_axis axis, t_tri_vec *left_tris, t_tri_vec *right_tris)
{
	t_vec3		mid_point;
	int			i;

	l3d_triangle_vec_midpoint(triangles, mid_point);
	i = -1;
	while (++i < (int)triangles->size)
	{
		l3d_triangle_vec_push(mid_point[axis] >=
			triangles->triangles[i]->center[axis] ? right_tris : left_tris,
			triangles->triangles[i]);
	}
}

static void			kd_node_print_recursive(t_kd_node *root)
{
	char	axes[4];

	axes[l3d_axis_x] = 'x';
	axes[l3d_axis_y] = 'y';
	axes[l3d_axis_z] = 'z';
	axes[l3d_axis_none] = 'n';
	if (root != NULL)
	{
		ft_printf("Triangles: %d\n", root->triangles->size);
		ft_printf("Depth: %d\n", root->depth);
		ft_printf("uuid: %d\nbbox.center: [%0.2f %0.2f %0.2f]\n"
			"axis: %c\n"
			"bbox.size: [%0.2f %0.2f %0.2f]\n"
			"bbox.min_xyz: [%0.2f %0.2f %0.2f]\n"
			"bbox.max_xyz: [%0.2f %0.2f %0.2f]\n",
			root->uuid, root->bounding_box.center[0],
			root->bounding_box.center[1], root->bounding_box.center[2],
			axes[root->axis], root->bounding_box.size[0],
			root->bounding_box.size[1], root->bounding_box.size[2],
			root->bounding_box.xyz_min[0], root->bounding_box.xyz_min[1],
			root->bounding_box.xyz_min[2], root->bounding_box.xyz_max[0],
			root->bounding_box.xyz_max[1], root->bounding_box.xyz_max[2]);
		kd_node_print_recursive(root->left);
		kd_node_print_recursive(root->right);
	}
}

void				l3d_kd_tree_print(t_kd_tree *tree)
{
	kd_node_print_recursive(tree->root);
}
