
#include <time.h>
#include "ms/ms.h"
#include "../debug.h"

static debug_t d1;
static debug_t d2;
static debug_t d3;

//
// To build, run `$ make examples/simple`.
//
// To see it in action, run `$ DEBUG=example:* examples/simple`.
//

int
main() {
  clock_t start = clock();

  debug_init(&d1, "example:foo");
  debug_init(&d2, "example:bar");
  debug_init(&d3, "example:baz");

  debug(&d2, "entering loop");

  for (int i = 0; i < 15; i++) {
    debug(&d1, "loop: %d", i);
  }

  char *diff = milliseconds_to_string(clock() - start);
  debug(&d3, "exiting loop after %s", diff);
  free(diff);

  return 0;
}
