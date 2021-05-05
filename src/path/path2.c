/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:26:00 by ahakanen          #+#    #+#             */
/*   Updated: 2021/04/07 14:29:37 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static t_path_node	*path_check_existing(t_doom3d *app, t_path_node *path_obj)
{
	t_path_node	*ret;
	int			i;

	i = path_obj->num_neighbors;
	while (--i > -1)
	{
		if (path_obj->neighbors[i] == app->editor.selected_objects[0])
			return ((ret = app->editor.selected_objects[0]->params));
	}
	return (NULL);
}

/*
** Deletes all connections of a node
** eg. for deletion of a node object
*/

void	delete_path_object_connections(t_path_node *src)
{
	t_path_node	*dst;
	int			i;

	i = src->num_neighbors;
	while (--i > -1)
		path_delete_connection(src, (dst = src->neighbors[i]->params));
}

/*
** Deletes the connection between two path nodes,
** then moves any nodes after the deleted nodes
** to fill the spot and updates neighbour counts of both nodes
*/

void	path_delete_connection(t_path_node *src, t_path_node *dst)
{
	int	i;
	int	j;

	i = src->num_neighbors;
	j = dst->num_neighbors;
	while (--i > 0)
		if (src->neighbors[i] == dst->parent_obj)
			break ;
	while (--j > 0)
		if (dst->neighbors[j] == src->parent_obj)
			break ;
	while (++i < src->num_neighbors)
		src->neighbors[i - 1] = src->neighbors[i];
	while (++j < dst->num_neighbors)
		dst->neighbors[j - 1] = dst->neighbors[j];
	src->num_neighbors--;
	dst->num_neighbors--;
	LOG_INFO("Deleted connection between obj %d and obj %d!",
		src->parent_obj->id, dst->parent_obj->id);
}

/*
** Connects t_path_node params inside t_3d_object so that they point
** to their nearest neighbors
** Then npcs can loop those to find where to move :)
*/

void	path_objects_set_neighbour(t_doom3d *app, t_3d_object *obj)
{
	t_path_node	*path_obj;
	t_path_node	*dest;
	t_path_node	*delete;

	if (obj == NULL)
		return ;
	path_obj = obj->params;
	dest = app->editor.selected_objects[0]->params;
	if (path_obj->num_neighbors >= PATH_NEIGHBOUR_MAX
		|| dest->num_neighbors >= PATH_NEIGHBOUR_MAX
		|| path_obj == dest)
		return ;
	delete = path_check_existing(app, path_obj);
	if (delete != NULL)
		path_delete_connection(path_obj, delete);
	else
	{
		path_obj->neighbors[path_obj->num_neighbors]
			= app->editor.selected_objects[0];
		dest->neighbors[dest->num_neighbors] = obj;
		path_obj->num_neighbors++;
		dest->num_neighbors++;
		LOG_INFO("Nodes connected successfully %d", obj->id);
	}
}
