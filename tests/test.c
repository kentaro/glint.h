#include <errno.h>
#include <stdio.h>
#include <unistd.h>

#include "glint.h"
#include "picotest/picotest.h"

void my_glint_callback(char *port) {
  execl("tests/test-server.rb", "ruby", port, (char *)NULL);
}

static void test_glint_new() {
    glint *self = glint_new(my_glint_callback);
    ok(self != NULL);
    glint_free(self);
}

static void test_glint_start() {
  glint *self = glint_new(my_glint_callback);

  bool res = glint_start(self);
  ok(res == true);

  glint_stop(self);
  glint_free(self);
}

static void test_glint_empty_port() {
    uint16_t port = glint_empty_port();
    ok(port != 0);
}

int main(int argc, char **argv) {
  subtest("glint_new", test_glint_new);
  subtest("glint_start", test_glint_start);
  subtest("glint_empty_port", test_glint_empty_port);
  return done_testing();
}