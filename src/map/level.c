/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 23:04:12 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/05 16:43:06 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Read map file list to be used as level for doom3d
** free previously read level list.
*/

void	read_level_list(t_doom3d *app)
{
	int32_t		fd;
	const char	*level_list;
	int32_t		i;

	i = -1;
	while (++i < (int32_t)app->num_levels)
		ft_strdel(&app->level_list[i]);
	ft_memset(app->level_list, 0, sizeof(app->level_list));
	level_list = "assets/map_data/level_list.txt";
	fd = open(level_list, O_RDONLY);
	if (fd == -1)
	{
		LOG_ERROR("Failed to open file %s", level_list);
		exit(EXIT_FAILURE);
		return ;
	}
	i = 0;
	while (get_next_line(fd, &app->level_list[i]))
	{
		ft_printf("%s\n", app->level_list[i]);
		i++;
	}
	app->num_levels = i;
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
	level_list = "assets/map_data/level_list.txt";
	fd = open(level_list, O_RDWR);
	if (fd == -1)
	{
		LOG_ERROR("Failed to open file %s", level_list);
		exit(EXIT_FAILURE);
	}
	while (get_next_line(fd, &level))
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
