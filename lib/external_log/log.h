/**
 * Copyright (c) 2020 rxi
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See `log.c` for details.
 */

#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdarg.h>
#include <time.h>

#define LOG_VERSION "0.1.0"

typedef struct {
  va_list ap;
  const char *fmt;
  const char *file;
  struct tm *time;
  void *udata;
  int line;
  int level;
} log_Event;

typedef void (*log_LogFn)(log_Event *ev);
typedef void (*log_LockFn)(int lock, void *udata);

enum { l_trace, l_debug, l_info, l_warn, l_error, l_fatal };

#define LOG_TRACE(...) log_log(l_trace, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_DEBUG(...) log_log(l_debug, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_INFO(...)  log_log(l_info,  __FILE__, __LINE__, __VA_ARGS__)
#define LOG_WARN(...)  log_log(l_warn,  __FILE__, __LINE__, __VA_ARGS__)
#define LOG_ERROR(...) log_log(l_error, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_FATAL(...) log_log(l_fatal, __FILE__, __LINE__, __VA_ARGS__)

const char* log_level_string(int level);
void log_set_lock(log_LockFn fn, void *udata);
void log_set_level(int level);
void log_set_quiet(int enable);
int log_add_callback(log_LogFn fn, void *udata, int level);
int log_add_fp(FILE *fp, int level);

void log_log(int level, const char *file, int line, const char *fmt, ...);

#endif
