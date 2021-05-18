/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/19 00:13:31 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	parse_args(t_doom3d *app, int32_t argc, char **argv)
{
	int32_t		fd;
	char		level1[128];

	if (argc > 1 && ft_strequ(argv[1], "--load-assets"))
		app->is_asset_load = true;
	else if (argc > 1 && ft_strequ(argv[1], "--old"))
	{
		app->is_asset_load = true;
		app->no_assets_in_first_map = true;
	}
	else
	{
		LOG_INFO("Start Doom App");
		ft_sprintf(level1, "assets/map_data/%s", FIRST_LEVEL);
		fd = open(level1, O_RDONLY);
		error_check(fd == -1, "Level1 not found. "
			"Level1 is needed for doom-nukem to run."
			" Create level1 with ./doom-nukem --load-assets");
		close(fd);
	}
	if (app->is_asset_load)
		LOG_INFO("Start Doom in Asset Load Mode, dont forget to save %s,"
			" which will contain shared assets", FIRST_LEVEL);
}

/*
** To load assets as a developer for the first map (FIRST_LEVEL),
** run ./doom-nukem --load-assets
** If you don't run doom with that mode, FIRST_LEVEL is required for the app
** to run.
*/

int32_t	main(int32_t argc, char **argv)
{
	t_doom3d	app;

	ft_memset(&app, 0, sizeof(t_doom3d));
	srand(time(NULL));
	parse_args(&app, argc, argv);
	doom3d_run(&app);
	return (EXIT_SUCCESS);
}
