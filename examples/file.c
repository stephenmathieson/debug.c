
#include "ms/ms.h"
#include "../debug.h"

static debug_t debugger;

//
// To build, run `$ make examples/simple`.
//
// To see it in action, run `$ DEBUG=example:* examples/simple`.
//

int
main() {
  debug_init(&debugger, "example:file");
  FILE *stream = fopen("./debug.txt", "w");
  debugger.stream = stream;

  for (int i = 0; i < 100; i++) {
    debug(&debugger, "%d", i);
  }

  fclose(stream);

  return 0;
}
