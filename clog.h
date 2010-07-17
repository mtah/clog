#ifndef _CLOG_H_
#define _CLOG_H_

#include <stdio.h>

typedef struct clog_out {
  FILE *stream;
  struct clog_out *next;
} clog_out;

typedef struct {
  clog_out *out;
} clog;

clog *clog_open(void);
void clog_close(clog *logger);
void clog_add_stream(clog *logger, FILE *stream);
void clog_add_path(clog *logger, const char *path);
void clog_log(const clog *logger, const char *level, const char *format, ...);

#define CLOG_LEVEL_OFF   11
#define CLOG_LEVEL_FATAL 9
#define CLOG_LEVEL_ERROR 7
#define CLOG_LEVEL_WARN  5
#define CLOG_LEVEL_INFO  3
#define CLOG_LEVEL_DEBUG 1

#ifndef CLOG_THRESHOLD
#define CLOG_THRESHOLD CLOG_LEVEL_ERROR
#endif

#if CLOG_THRESHOLD <= CLOG_LEVEL_FATAL
#define clog_fatal(logger, format, ...) clog_log(logger, "fatal", format, ##__VA_ARGS__)
#else
#define clog_fatal(logger, format, ...)
#endif

#if CLOG_THRESHOLD <= CLOG_LEVEL_ERROR
#define clog_error(logger, format, ...) clog_log(logger, "error", format, ##__VA_ARGS__)
#else
#define clog_error(logger, format, ...)
#endif

#if CLOG_THRESHOLD <= CLOG_LEVEL_WARN
#define clog_warn(logger, format, ...) clog_log(logger, "warn", format, ##__VA_ARGS__)
#else
#define clog_warn(logger, format, ...)
#endif

#if CLOG_THRESHOLD <= CLOG_LEVEL_INFO
#define clog_info(logger, format, ...) clog_log(logger, "info", format, ##__VA_ARGS__)
#else
#define clog_info(logger, format, ...)
#endif

#if CLOG_THRESHOLD <= CLOG_LEVEL_DEBUG
#define clog_debug(logger, format, ...) clog_log(logger, "debug", format, ##__VA_ARGS__)
#else
#define clog_debug(logger, format, ...)
#endif

#endif /* _CLOG_H_ */
