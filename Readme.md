
# debug.c

  Conditional debugging for C libraries and applications.  Based off of [visionmedia/debug](https://github.com/visionmedia/debug) and [tj/go-debug](https://github.com/tj/go-debug).

## Usage

```c
#include "debug.h"

debug_t debugger;

int
main() {
  // init debugger
  debug_init(&debugger, "myapp");
  // log a message
  debug(&debugger, "doing stuff");
  return 0;
}
```

## Environment Variables

### DEBUG

  Set `DEBUG` to see output from your application.  When set to `app` (`DEBUG=app`), you'll see messages from the debugger named `app`.  When set to `app*` (`DEBUG=app*`), you'll see debug messages from all debuggers whose name begins with `app`.

  You may also set `DEBUG=*` to see *all* debugging messages.

### DEBUG_COLORS

  Set `DEBUG_COLORS` to `0`, `no`, `disabled` or `false` to not use ANSI-escape sequences when printing debug messages.

  If `DEBUG_COLORS` is not set, and `debugger.stream` is a TTY, colors will be used.

## STDIO

  By default, `debug` prints to `stderr`.  If you don't like this behavior, you may set the stream to any arbitrary `FILE *`:

```c
FILE *fp = fopen("debugs.txt", "w");
debug_t debugger;
debug_init(&debugger, "whatever");
debugger.stream = fp;
debug(&debugger, "hi");
```

## License

  MIT
