/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 15:03:32 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/06 01:51:41 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "logger.h"
#include <time.h>
#include "ft_printf.h"

static const char	*get_level_color(t_log_level level)
{
	const char	*color;

	color = TRACE_COLOR_PRINT;
	if (level == level_debug)
		color = DEBUG_COLOR_PRINT;
	else if (level == level_info)
		color = INFO_COLOR_PRINT;
	else if (level == level_warn)
		color = WARN_COLOR_PRINT;
	else if (level == level_error)
		color = ERROR_COLOR_PRINT;
	else if (level == level_fatal)
		color = FATAL_COLOR_PRINT;
	return (color);
}

static const char	*get_level_string(t_log_level level)
{
	const char	*color;

	color = TRACE_COLOR_STR;
	if (level == level_debug)
		color = DEBUG_COLOR_STR;
	else if (level == level_info)
		color = INFO_COLOR_STR;
	else if (level == level_warn)
		color = WARN_COLOR_STR;
	else if (level == level_error)
		color = ERROR_COLOR_STR;
	else if (level == level_fatal)
		color = FATAL_COLOR_STR;
	return (color);
}

void				logger_log(int32_t level,
						const char *file,
						int32_t line,
						const char *fmt,
						...)
{
	char	time_buf[64];
	time_t	event_time;
	va_list	args;
	int32_t	len;

	event_time = time(NULL);
	len = strftime(time_buf, sizeof(time_buf), "%H:%M:%S",
		localtime(&event_time));
	time_buf[len] = '\0';
	ft_printf("%s %s%-5s\x1b[0m \x1b[90m%s:%d:\x1b[0m ",
		time_buf,
		get_level_color(level),
		get_level_string(level),
		file,
		line);
	va_start(args, fmt);
	ft_vprintf(fmt, args);
	ft_putchar('\n');
	va_end(args);
}
