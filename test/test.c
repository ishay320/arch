#include "fast_tests.h"

#include <stdio.h>

int main(int argc, char const* argv[])
{
    int x = 0;
    TEST_EQ_INT(1, ++x, "fine");
    SUCCESS("all test ran successfully");
    return 0;
}
