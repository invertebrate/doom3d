/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_kd_tree_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:22:07 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/09 20:57:39 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d_internals.h"

/*
** Destroys a kd node and its children leaving triangles intact, though the
** triangle vector is deleted.
*/

void	l3d_kd_node_destroy(t_kd_node *root)
{
	if (root)
	{
		l3d_triangle_vec_delete(root->triangles);
		l3d_kd_node_destroy(root->left);
		l3d_kd_node_destroy(root->right);
		free(root);
		root = NULL;
	}
}

/*
** Creates a kd tree node from a triangle vector initializing its values.
*/

t_kd_node	*l3d_kd_node_create(t_tri_vec *triangles)
{
	t_kd_node	*node;

	node = ft_calloc(sizeof(t_kd_node));
	if (!node)
		return (NULL);
	l3d_bounding_box_set(triangles, &node->bounding_box);
	node->triangles = triangles;
	node->left = NULL;
	node->right = NULL;
	node->axis = l3d_axis_none;
	return (node);
}
