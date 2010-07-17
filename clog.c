#include "clog.h"
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>



/*
 *  Auxiliary prototypes 
 * 
 */

void _clog_add_out(clog *logger, clog_out *out);



/*
 * Header implementation 
 *
 */

clog *clog_open(void) {
  clog *logger = malloc(sizeof *logger);
  logger->out = NULL;
  return logger;
}

void clog_close(clog *logger) {
  clog_out *tmp, *out = logger->out;

  while(out) {
    if (out->stream && out->managed) fclose(out->stream);
    tmp = out;
    out = out->next;
    free(tmp);
  }

  free(logger);
}

void clog_add_stream(clog *logger, FILE *stream) {
  clog_out out = { .stream = stream, .managed = 0, .next = logger->out };
  _clog_add_out(logger, &out);
}

void clog_add_path(clog *logger, const char *path) {
  FILE *stream = fopen(path, "a");
  clog_out out = { .stream = stream, .managed = 1, .next = logger->out };
  _clog_add_out(logger, &out);
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



/*
 * Auxiliary implementation
 *
 */
void _clog_add_out(clog *logger, clog_out *out) {
  clog_out *tmp = malloc(sizeof *tmp);
  memcpy(tmp, out, sizeof *tmp);
  logger->out = tmp;
}
