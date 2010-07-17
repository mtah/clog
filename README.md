clog is a simplistic logging library written in C.

## Example usage

    #include <clog.h>

    int main(int argc, char *argv[])
    {
      clog *logger = clog_open();
      clog_add_stream(logger, stderr);
      clog_add_path(logger, "example.log");

      clog_fatal(logger, "This is a fatal error message.");
      clog_error(logger, "This is a regular error message.");
      clog_warn(logger, "This is a warning message.");
      clog_info(logger, "This is an informative message.");
      clog_debug(logger, "This is a debug message.");

      clog_close(logger);

      return 0;
    }

The log level threshold can be configured at compile-time by setting the
`CLOG_THRESHOLD` preprocessor directive to one of `CLOG_LEVEL_DEBUG`,
`CLOG_LEVEL_INFO`, `CLOG_LEVEL_WARN`, `CLOG_LEVEL_ERROR`,
`CLOG_LEVEL_FATAL` or `CLOG_LEVEL_OFF` (turning off logging
completely) like so:

    gcc -DCLOG_THRESHOLD=CLOG_LEVEL_ERROR example.c -o example

This will cause only calls to `clog_error` and `clog_fatal` to produce
output, which is also the default if `CLOG_THRESHOLD` is omitted.

## License

Copyright (c) 2010 Martin Häger

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.           
