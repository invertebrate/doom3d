/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_kd_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:22:07 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/06 17:22:54 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d_internals.h"

/*
** Splits triangles by longest axis and until max depth has been reached or
** minimum number of node triangles have been reached.
*/

static t_kd_node	*tree_create_recursive(t_tri_vec *triangles, uint32_t depth,
					uint32_t *num_nodes)
{
	t_kd_node	*node;
	t_tri_vec	*left_tris;
	t_tri_vec	*right_tris;

	node = l3d_kd_node_create(triangles);
	node->uuid = (*num_nodes)++;
	node->depth = depth;
	if (triangles->size == 0 || triangles->size == 1)
		return (node);
	node->axis = l3d_bounding_box_longest_axis(node->bounding_box);
	left_tris = l3d_triangle_vec_empty();
	right_tris = l3d_triangle_vec_empty();
	l3d_kd_tree_split_triangles(triangles, node->axis, left_tris, right_tris);
	if ((left_tris->size < L3D_MIN_KD_NODE_NUM_TRIANGLES ||
		right_tris->size < L3D_MIN_KD_NODE_NUM_TRIANGLES) ||
		depth >= L3D_MAX_KD_TREE_DEPTH)
	{
		l3d_triangle_vec_delete(left_tris);
		l3d_triangle_vec_delete(right_tris);
		return (node);
	}
	node->left = tree_create_recursive(left_tris, depth + 1, num_nodes);
	node->right = tree_create_recursive(right_tris, depth + 1, num_nodes);
	return (node);
}

/*
** Creates a kd tree structure from triangles for faster bounding box & triangle
** hit search.
*/

t_kd_tree			*l3d_kd_tree_create(t_triangle **triangles,
					uint32_t num_triangles)
{
	t_kd_tree		*tree;
	t_tri_vec		*triangle_vector;

	if (!(tree = malloc(sizeof(t_kd_tree))))
		return (NULL);
	triangle_vector = l3d_triangle_vec(triangles, num_triangles);
	tree->num_nodes = 0;
	tree->root = tree_create_recursive(triangle_vector, 0, &tree->num_nodes);
	return (tree);
}

/*
** Destroys kd tree and frees it memory. Triangles stay intact.
*/

void				l3d_kd_tree_destroy(t_kd_tree *tree)
{
	l3d_kd_node_destroy(tree->root);
	free(tree);
	tree = NULL;
}

/*
** Destroys previous tree and creates a new one from updated triangles.
** This is to be used after triangle vertices have been changed.
*/

void				l3d_kd_tree_create_or_update(t_kd_tree **tree,
					t_triangle **triangles, uint32_t num_triangles)
{
	if (tree && *tree)
		l3d_kd_tree_destroy(*tree);
	*tree = l3d_kd_tree_create(triangles, num_triangles);
}
