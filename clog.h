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
void *clog_close(clog *logger);
void *clog_add_stream(clog *logger, FILE *stream);
void *clog_add_path(clog *logger, const char *path);
void clog_log(const clog *logger, const char *level, const char *format, ...);

#define clog_fatal(logger, format, ...) clog_log(logger, "fatal", format, ##__VA_ARGS__)
#define clog_error(logger, format, ...) clog_log(logger, "error", format, ##__VA_ARGS__)
#define clog_warn(logger, format, ...) clog_log(logger, "warn", format, ##__VA_ARGS__)
#define clog_info(logger, format, ...) clog_log(logger, "info", format, ##__VA_ARGS__)
#define clog_debug(logger, format, ...) clog_log(logger, "debug", format, ##__VA_ARGS__)

#endif /* _CLOG_H_ */
