#include "clog.h"
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>

clog *clog_open(void) {
  clog *logger = malloc(sizeof(clog));
  logger->out = NULL;
  return logger;
}

void clog_close(clog *logger) {
  clog_out *tmp, *out = logger->out;

  while(out) {
    if (out->stream) fclose(out->stream);
    tmp = out;
    out = out->next;
    free(tmp);
  }

  free(logger);
}

void clog_add_stream(clog *logger, FILE *stream) {
  clog_out *out = malloc(sizeof(clog_out));
  out->stream = stream;
  out->next = logger->out;
  logger->out = out;
}

void clog_add_path(clog *logger, const char *path) {
  FILE *stream = fopen(path, "a");

  clog_add_stream(logger, stream);
}

void clog_log(const clog *logger, const char *level, const char *format, ...) {
  va_list params;

  time_t t = time(NULL);
  char time_str[32];
  strftime(time_str, 32, "%Y-%m-%d %H:%M:%S", localtime(&t));

  clog_out *out = logger->out;
  while(out) {
    fprintf(out->stream, "(%s) [%s] ", time_str, level);
    va_start(params, format);
    vfprintf(out->stream, format, params);
    va_end(params);
    fprintf(out->stream, "\n");
    
    out = out->next;
  }
}
