/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 23:04:12 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/29 19:45:39 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	init_level_list(t_doom3d *app)
{
	int32_t		i;

	i = -1;
	while (++i < (int32_t)app->num_levels)
		ft_strdel(&app->level_list[i]);
	ft_memset(app->level_list, 0, sizeof(app->level_list));
	app->level_list[0] = ft_strdup(FIRST_LEVEL);
	app->num_levels = 0;
}

/*
** Read map file list to be used as level for doom3d
** free previously read level list.
*/

void	read_level_list(t_doom3d *app)
{
	int32_t		fd;
	const char	*level_list;
	int32_t		i;

	init_level_list(app);
	level_list = "level_list.txt";
	fd = open(level_list, O_RDONLY | O_CREAT, 0644);
	if (fd == -1)
	{
		LOG_ERROR("Failed to open file %s", level_list);
		exit(EXIT_FAILURE);
		return ;
	}
	i = 1;
	while (get_next_line(fd, &app->level_list[i]) > 0)
		i++;
	app->num_levels += i;
	if (close(fd) == -1)
	{
		LOG_ERROR("Failed to close file %s", level_list);
		exit(EXIT_FAILURE);
	}
}

void	write_savename_to_level_list(t_doom3d *app)
{
	int32_t		fd;
	const char	*level_list;
	char		*level;
	int32_t		ret;

	level = NULL;
	level_list = "level_list.txt";
	fd = open(level_list, O_RDWR | O_CREAT, 0644);
	if (fd == -1)
	{
		LOG_ERROR("Failed to open file %s", level_list);
		exit(EXIT_FAILURE);
	}
	while (get_next_line(fd, &level) > 0)
		ft_strdel(&level);
	ret = write(fd, app->editor.editor_filename,
			ft_strlen(app->editor.editor_filename));
	ret = write(fd, "\n", 1);
	(void)ret;
	if (close(fd) == -1)
	{
		LOG_ERROR("Failed to close file %s", level_list);
		exit(EXIT_FAILURE);
	}
	read_level_list(app);
}
