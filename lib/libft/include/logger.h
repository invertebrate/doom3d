/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 14:44:34 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/05 14:48:10 by ohakola          ###   ########.fr       */
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

typedef enum e_log_level
{
	l_trace,
	l_debug,
	l_info,
	l_warn,
	l_error,
	l_fatal,
}					t_log_level;

typedef struct s_log
{
	int32_t		level;
	const char	*file;
	int32_t		line;
}					t_log;

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

/*
** Log traces like you'd use ft_printf LOG_TRACE("%s", "hello")
*/

# define LOG_TRACE(...) logger(log_p(l_trace, __FILE__, __LINE__), __VA_ARGS__)

/*
** Log debug information like you'd use ft_printf LOG_DEBUG("%s", "hello")
*/

# define LOG_DEBUG(...) logger(log_p(l_debug, __FILE__, __LINE__), __VA_ARGS__)

/*
** Log information like you'd use ft_printf LOG_INFO("%s", "hello")
*/

# define LOG_INFO(...) logger(log_p(l_info,  __FILE__, __LINE__), __VA_ARGS__)

/*
** Log warnings like you'd use ft_printf LOG_WARN("%s", "hello")
*/

# define LOG_WARN(...) logger(log_p(l_warn,  __FILE__, __LINE__), __VA_ARGS__)

/*
** Log errors like you'd use ft_printf LOG_ERROR("%s", "hello")
*/

# define LOG_ERROR(...) logger(log_p(l_error, __FILE__, __LINE__), __VA_ARGS__)

/*
** Log crashing / fatal errors like you'd use ft_printf LOG_FATAL("%s", "hello")
*/

# define LOG_FATAL(...) logger(log_p(l_fatal, __FILE__, __LINE__), __VA_ARGS__)


void				logger(t_log params, const char *fmt, ...);
t_log				log_p(int32_t level, const char *file, int32_t line);

#endif
