
CC ?= cc
OS = $(shell uname)
CFLAGS += -std=c99 -Wall -Wextra -Ideps
LDFLAGS =
DEPS = $(wildcard deps/*/*.c)
DEP_OBJS = $(DEPS:.c=.o)
EXAMPLE_SRC = $(wildcard examples/*.c)
EXAMPLE_OBJS = $(EXAMPLE_SRC:.c=.o)
EXAMPLES = $(EXAMPLE_SRC:.c=)
VALGRIND ?= valgrind
VALGRIND_OPTS = --leak-check=full --error-exitcode=1

ifeq ($(OS), Linux)
	LDFLAGS = -lpthread
endif

examples: $(DEP_OBJS) $(EXAMPLE_OBJS) $(EXAMPLES)

examples/%: examples/%.o $(DEP_OBJS) debug.o
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS)

clean:
	rm -f debug.o $(EXAMPLES) $(EXAMPLE_OBJS) $(DEP_OBJS)

valgrind: examples/simple examples/threads examples/file
	DEBUG=a,b*,c,d,e,f,foo,bar,baz,app* \
	  $(VALGRIND) \
	    $(VALGRIND_OPTS) \
	      examples/threads
	DEBUG=foo,bar,baz,example,example:*,qux,mux \
	  $(VALGRIND) \
	    $(VALGRIND_OPTS) \
	      examples/simple
	DEBUG=examples* DEBUG_COLORS=yes \
	  $(VALGRIND) \
	    $(VALGRIND_OPTS) \
	      examples/file

.PHONY: default clean valgrind
