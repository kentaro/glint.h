#include <stdio.h>

#include "glint.h"
#include "picotest/picotest.h"

static void test_glint_empty_port() {
    uint16_t port = glint_empty_port();
    printf("%d\n", port);
    ok(port != 0);
}

int main(int argc, char **argv)
{
    subtest("glint_empty_port", test_glint_empty_port);
    return done_testing();
}