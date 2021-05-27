/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/27 18:54:56 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	parse_args(t_doom3d *app, int32_t argc, char **argv)
{
	int32_t		i;

	i = 0;
	while (++i < argc)
	{
		if (ft_strequ(argv[i], "--load-assets"))
			app->settings.is_asset_load = true;
		if (ft_strequ(argv[i], "--convert-assets"))
		{
			app->settings.is_asset_conversion = true;
			app->settings.is_asset_load = true;
		}
		if (ft_strequ(argv[i], "--debug"))
			app->settings.is_debug = true;
		if (ft_strequ(argv[i], "--default"))
		{
			app->settings.is_asset_load = true;
			app->settings.is_asset_conversion = false;
			app->settings.is_default_map_format = true;
		}
	}
}

static void	check_args(t_doom3d *app, int32_t argc, char **argv)
{
	parse_args(app, argc, argv);
	if (!app->settings.is_asset_load)
		LOG_INFO("Start Doom");
	else if (!app->settings.is_default_map_format)
		LOG_INFO("Start Doom in Asset Load Mode, dont forget to save %s,"
			" which will contain shared assets", FIRST_LEVEL);
	else
		LOG_INFO("Start Doom in Default Map Mode. Saving won't save assets to"
			" %s. Map should be valid old map (starts MAP)", FIRST_LEVEL);
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
	check_args(&app, argc, argv);
	doom3d_run(&app);
	return (EXIT_SUCCESS);
}
