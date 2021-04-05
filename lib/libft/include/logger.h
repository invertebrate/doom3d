/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 14:44:34 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/05 15:29:23 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGER_H
# define LOGGER_H

# include <stdint.h>
# include <stdarg.h>

/*
** Modified and simplified version of
** https://github.com/rxi/log.c
*/

typedef enum		e_log_level
{
	level_trace,
	level_debug,
	level_info,
	level_warn,
	level_error,
	level_fatal,
}					t_log_level;

# define TRACE_COLOR_PRINT "\x1b[94m"
# define DEBUG_COLOR_PRINT "\x1b[36m"
# define INFO_COLOR_PRINT "\x1b[32m"
# define WARN_COLOR_PRINT "\x1b[33m"
# define ERROR_COLOR_PRINT "\x1b[31m"
# define FATAL_COLOR_PRINT "\x1b[35m"

# define TRACE_COLOR_STR "TRACE"
# define DEBUG_COLOR_STR "DEBUG"
# define INFO_COLOR_STR "INFO"
# define WARN_COLOR_STR "WARN"
# define ERROR_COLOR_STR "ERROR"
# define FATAL_COLOR_STR "FATAL"

# define LOG_TRACE(...) logger_log(level_trace, __FILE__, __LINE__, __VA_ARGS__)
# define LOG_DEBUG(...) logger_log(level_debug, __FILE__, __LINE__, __VA_ARGS__)
# define LOG_INFO(...) logger_log(level_info,  __FILE__, __LINE__, __VA_ARGS__)
# define LOG_WARN(...) logger_log(level_warn,  __FILE__, __LINE__, __VA_ARGS__)
# define LOG_ERROR(...) logger_log(level_error, __FILE__, __LINE__, __VA_ARGS__)
# define LOG_FATAL(...) logger_log(level_fatal, __FILE__, __LINE__, __VA_ARGS__)

void				logger_log(int32_t level,
						const char *file,
						int32_t line,
						const char *fmt, ...);

#endif
