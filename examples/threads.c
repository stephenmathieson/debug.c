
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../debug.h"

//
// To build, run `$ make examples/threads`.
//
// To see it in action, run `$ DEBUG=app* examples/threads`.
//

debug_t app;
debug_t worker;

void *
do_work(void *arg) {
  for (int i = 0; i < 10; ++i) {
    debug(&worker, "doing some work (%d)", i);
    sleep(1);
  }
  pthread_exit(0);
}

int
main() {
  int rc;
  pthread_t thread;

  debug_init(&app, "app");
  debug_init(&worker, "app:worker");

  debug(&app, "booting application");

  rc = pthread_create(&thread, NULL, &do_work, NULL);
  if (0 != rc) perror("pthread_create"), exit(1);

  sleep(10);

  debug(&app, "killing worker");
  pthread_join(thread, NULL);

  debug(&app, "done ;)");
  return 0;
}
