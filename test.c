#include <stdio.h>

#include "glint.h"
#include "picotest/picotest.h"

static void test_glint_new() {
    glint *self = glint_new();
    ok(self != NULL);
    glint_free(self);
}

static void test_glint_empty_port() {
    uint16_t port = glint_empty_port();
    ok(port != 0);
}

int main(int argc, char **argv)
{
    subtest("glint_new", test_glint_new);
    subtest("glint_empty_port", test_glint_empty_port);
    return done_testing();
}