/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notifications.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 16:14:00 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/01 16:10:32 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void			update_notifications(t_doom3d *app)
{
	t_notification	*last_notification;
	t_list			**last_node;

	last_node = &app->notifications;
	if (!*last_node)
		return ;
	while ((*last_node)->next)
		last_node = &(*last_node)->next;
	last_notification = (*last_node)->content;
	last_notification->time -= app->info.delta_time;
	if (last_notification->time <= 0)
	{
		free(last_notification);
		free(*last_node);
		*last_node = NULL;
	}
}

void			notify_user(t_doom3d *app,
					t_notification notification)
{
	if (app->notifications == NULL)
		app->notifications = ft_lstnew(&notification, sizeof(t_notification));
	else
		ft_lstadd(&app->notifications,
			ft_lstnew(&notification, sizeof(t_notification)));
}

void			delete_notifications(t_doom3d *app)
{
	t_list		*node;
	t_list		*tmp;

	node = app->notifications;
	while (node)
	{
		tmp = node;
		free((t_notification*)node->content);
		node = node->next;
		free(tmp);
	}
	app->notifications = NULL;
}
