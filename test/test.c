#define ARCH_IMPLEMENTATION
#include "../arc.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define TEST_FILE_PATH "./tests_compare/"
#define TEST_FILE_POSTFIX ".png"
#define CREATE_TEST_OUTPUT(name) TEST_FILE_PATH name TEST_FILE_POSTFIX

#define HEIGHT 64
#define WIDTH 64

typedef enum
{
    TEST_PASS = 0,
    TEST_FAIL,
    TEST_WRITTEN,
    TEST_STATUS_NUM
} TestStatus;

TestStatus readWriteCompareCanvas(const arch_Canvas* canvas_a, arch_Canvas* canvas_b, const char* file_path, char read_write);
int GetStatusStr(TestStatus status, char** test_status, char** test_color);

int test_fill(char read_write)
{
    uint32_t data[sizeof(uint32_t) * HEIGHT * WIDTH];
    arch_Canvas canvas = {.data = data, .width = WIDTH, .height = HEIGHT};
    arch_fill(&canvas, ARCH_RED);

    uint32_t data_compare[sizeof(uint32_t) * HEIGHT * WIDTH];
    arch_Canvas canvas_compare = {.data = data_compare, .width = WIDTH, .height = HEIGHT};

    return readWriteCompareCanvas(&canvas, &canvas_compare, CREATE_TEST_OUTPUT("fill"), read_write);
}

int test_circle(char read_write)
{
    uint32_t data[sizeof(uint32_t) * HEIGHT * WIDTH];
    arch_Canvas canvas = {.data = data, .width = WIDTH, .height = HEIGHT};
    arch_fill(&canvas, ARCH_RED);
    arch_circle(&canvas, ARCH_BLUE, canvas.width / 2, canvas.height / 2, 10);

    uint32_t data_compare[sizeof(uint32_t) * HEIGHT * WIDTH];
    arch_Canvas canvas_compare = {.data = data_compare, .width = WIDTH, .height = HEIGHT};

    return readWriteCompareCanvas(&canvas, &canvas_compare, CREATE_TEST_OUTPUT("circle"), read_write);
}

int test_rectangle(char read_write)
{
    uint32_t data[sizeof(uint32_t) * HEIGHT * WIDTH];
    arch_Canvas canvas = {.data = data, .width = WIDTH, .height = HEIGHT};
    arch_fill(&canvas, ARCH_RED);
    arch_rectangle(&canvas, ARCH_WHITE, canvas.width / 4, canvas.height / 4, 3 * canvas.width / 4, 3 * canvas.height / 4);

    uint32_t data_compare[sizeof(uint32_t) * HEIGHT * WIDTH];
    arch_Canvas canvas_compare = {.data = data_compare, .width = WIDTH, .height = HEIGHT};

    return readWriteCompareCanvas(&canvas, &canvas_compare, CREATE_TEST_OUTPUT("rectangle"), read_write);
}

struct function_pair
{
    int (*fun)(char);
    const char* name;
};

// Fill it with new tests
struct function_pair tests[] = {{test_circle, "circle"}, {test_rectangle, "rectangle"}, {test_fill, "fill"}};

int main(int argc, char const* argv[])
{
    // Default is read
    const char command = (argc > 1) ? *argv[1] : 'r';
    size_t num_tests   = sizeof(tests) / sizeof(tests[0]);

    int err = 0;
    for (size_t i = 0; i < num_tests; i++)
    {
        /* before tests */
        err = tests[i].fun(command);
        /* after tests */

        // Print out the test status
        char* test_status;
        char* test_color;
        if (GetStatusStr(err, &test_status, &test_color) == 1)
        {
            return 1;
        }

        printf("TEST %ld/%ld %s %s[%s]\033[0m\n", i + 1, num_tests, tests[i].name, test_color, test_status);
    }

    return 0;
}

int GetStatusStr(TestStatus status, char** test_status, char** test_color)
{
    static char* test_ok            = "OK";
    static char* test_ok_color      = "\033[32m";
    static char* test_fail          = "FAIL";
    static char* test_fail_color    = "\033[31m";
    static char* test_written       = "WRITTEN";
    static char* test_written_color = "\033[33m";

    static_assert(TEST_STATUS_NUM == 3, "ERROR: TestStatus was not updated, add case for the new test option\n");
    switch (status)
    {
        case TEST_PASS:
        {
            *test_status = test_ok;
            *test_color  = test_ok_color;
        }
        break;
        case TEST_FAIL:
        {
            *test_status = test_fail;
            *test_color  = test_fail_color;
        }
        break;
        case TEST_WRITTEN:
        {
            *test_status = test_written;
            *test_color  = test_written_color;
        }
        break;

        default:
            printf("%s:%d how did you got here?!", __FILE__, __LINE__);
            return 1;
            break;
    }
    return 0;
}

TestStatus readWriteCompareCanvas(const arch_Canvas* canvas_a, arch_Canvas* canvas_b, const char* file_path, char read_write)
{
    switch (read_write)
    {
        case 'r':
        {
            canvas_b->data = (uint32_t*)stbi_load(file_path, (int*)&canvas_b->width, (int*)&canvas_b->height, 0, 4);

            if (canvas_b->data == 0)
            {
                printf("ERROR: read file \"%s\": %s\n", file_path, strerror(errno));
                return TEST_FAIL;
            }

            if (canvas_b->width != canvas_a->width || canvas_b->height != canvas_a->height)
            {
                printf("ERROR: sizes wont match up\n");
                return TEST_FAIL;
            }
        }
        break;
        case 'w':
        {
            if (stbi_write_png(file_path, canvas_a->width, canvas_a->height, 4, canvas_a->data, 0) == 0)
            {
                printf("ERROR: write file failed: %s\n", strerror(errno));
                return TEST_FAIL;
            }
            return TEST_WRITTEN;
        }
        break;

        default:
            printf("ERROR: input is not 'r'/'w'\n");
            return TEST_FAIL;
            break;
    }

    for (size_t i = 0; i < HEIGHT * WIDTH; i++)
    {
        if (canvas_a->data[i] != canvas_b->data[i])
        {
            printf("ERROR: 0x%08X and 0x%08X in pos %ld won`t match up\n", canvas_a->data[i], canvas_b->data[i], i);
            return TEST_FAIL;
        }
    }

    STBI_FREE(canvas_b->data);
    return TEST_PASS;
}
