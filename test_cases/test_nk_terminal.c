/*
 * test_nk_array.cpp
 *
 *  Created on: Feb 21, 2021
 *      Author: nenad
 */

#include <stdbool.h>

#include "../nk_test.h"
#include "test_nk_terminal.h"
#include "generic/nk_string.h"
#include "generic/terminal/nk_terminal.h"

#if defined(NK_ENABLED_TERMINAL)

struct simple__terminal_commands
    NK_ARRAY__BUCKET_TYPED_T(const struct terminal__command_descriptor *, 1, struct terminal_commands)
simple__terminal_commands =
NK_ARRAY__BUCKET_INITIALIZER_EMPTY(&simple__terminal_commands);

static const char*
simple__command_function(void *terminal_context,
                         void *command_context,
                         struct terminal_arguments *args,
                         struct nk_string *output)
{
    int *terminal = terminal_context;
    int *command = command_context;

    if (terminal) {
        *terminal += 10;
    }
    if (command) {
        *command += 11;
    }
    nk_string__append_literal(output, NK_STRING__LITERAL("test output"));
    /* Start from 1 skipping the command name */
    for (size_t i = 1u; i < args->length; i++) {
        nk_string__append_literal(output, NK_STRING__LITERAL(" arg:"));
        nk_string__append(output, &args->items[i]);
    }
    return NULL;
}

static void
test__simple__parse_empty(void)
{
    struct terminal_descriptor terminal;
    int terminal_context = 4;
    int command_context = 8;
    struct working_buffer
        NK_STRING__BUCKET_T(500)
    working_buffer = NK_STRING__BUCKET_INITIALIZER_EMPTY(&working_buffer);
    struct error_message
        NK_STRING__BUCKET_T(500)
    error_message = NK_STRING__BUCKET_INITIALIZER_EMPTY(&error_message);
    struct input
        NK_STRING__BUCKET_T(500)
    input = NK_STRING__BUCKET_INITIALIZER_EMPTY(&input);
    struct output
        NK_STRING__BUCKET_T(500)
    output = NK_STRING__BUCKET_INITIALIZER_EMPTY(&output);
    struct
        NK_STRING__BUCKET_T(100)
    command_id = NK_STRING__BUCKET_INITIALIZER(&command_id, "command");
    const struct terminal__command_descriptor command_1 = { .command_id = &command_id.array, .interpreter = { .fn =
                    simple__command_function, .command_context = &command_context } };
    simple__terminal_commands.array.items[0] = &command_1;
    simple__terminal_commands.array.length = 1;
    terminal__init(&terminal, &simple__terminal_commands.array, &working_buffer.array, &error_message.array);
    terminal__set_terminal_context(&terminal, &terminal_context);
    terminal__interpret(&terminal, &input.array, &output.array);
    NK_TEST__EXPECT_INT(4);
    NK_TEST__ACTUAL_INT(terminal_context);
    NK_TEST__EXPECT_INT(8);
    NK_TEST__ACTUAL_INT(command_context);
    NK_TEST__EXPECT_SIZE(0);
    NK_TEST__ACTUAL_SIZE(output.array.length);
}

static void
test__simple__parse_a_letter(void)
{
    struct terminal_descriptor terminal;
    int terminal_context = 4;
    int command_context = 8;
    struct
        NK_STRING__BUCKET_T(500)
    working_buffer = NK_STRING__BUCKET_INITIALIZER_EMPTY(&working_buffer);
    struct
        NK_STRING__BUCKET_T(500)
    error_message = NK_STRING__BUCKET_INITIALIZER_EMPTY(&error_message);
    struct
        NK_STRING__BUCKET_T(500)
    input = NK_STRING__BUCKET_INITIALIZER(&input, "a");
    struct
        NK_STRING__BUCKET_T(500)
    output = NK_STRING__BUCKET_INITIALIZER_EMPTY(&output);
    struct
        NK_STRING__BUCKET_T(100)
    command_id = NK_STRING__BUCKET_INITIALIZER(&command_id, "command");
    const struct terminal__command_descriptor command_1 = { .command_id = &command_id.array, .interpreter = { .fn =
                    simple__command_function, .command_context = &command_context } };
    simple__terminal_commands.array.items[0] = &command_1;
    simple__terminal_commands.array.length = 1;
    terminal__init(&terminal, &simple__terminal_commands.array, &working_buffer.array, &error_message.array);
    terminal__set_terminal_context(&terminal, &terminal_context);
    terminal__interpret(&terminal, &input.array, &output.array);
    NK_TEST__EXPECT_INT(4);
    NK_TEST__ACTUAL_INT(terminal_context);
    NK_TEST__EXPECT_INT(8);
    NK_TEST__ACTUAL_INT(command_context);
    NK_TEST__EXPECT_BOOL(true);
    NK_TEST__ACTUAL_BOOL(nk_string__is_equal(&input.array, &output.array));
}

static void
test__simple__parse_command_no_enter(void)
{
    struct terminal_descriptor terminal;
    int terminal_context = 4;
    int command_context = 8;
    struct working_buffer
        NK_STRING__BUCKET_T(500)
    working_buffer = NK_STRING__BUCKET_INITIALIZER_EMPTY(&working_buffer);
    struct error_message
        NK_STRING__BUCKET_T(500)
    error_message = NK_STRING__BUCKET_INITIALIZER_EMPTY(&error_message);
    struct input
        NK_STRING__BUCKET_T(500)
    input = NK_STRING__BUCKET_INITIALIZER(&input, "command");
    struct output
        NK_STRING__BUCKET_T(500)
    output = NK_STRING__BUCKET_INITIALIZER_EMPTY(&output);
    struct
        NK_STRING__BUCKET_T(100)
    command_id = NK_STRING__BUCKET_INITIALIZER(&command_id, "command");
    const struct terminal__command_descriptor command_1 = { .command_id = &command_id.array, .interpreter = { .fn =
                    simple__command_function, .command_context = &command_context } };
    simple__terminal_commands.array.items[0] = &command_1;
    simple__terminal_commands.array.length = 1;
    terminal__init(&terminal, &simple__terminal_commands.array, &working_buffer.array, &error_message.array);
    terminal__set_terminal_context(&terminal, &terminal_context);
    terminal__interpret(&terminal, &input.array, &output.array);
    NK_TEST__EXPECT_INT(4);
    NK_TEST__ACTUAL_INT(terminal_context);
    NK_TEST__EXPECT_INT(8);
    NK_TEST__ACTUAL_INT(command_context);
    NK_TEST__EXPECT_BOOL(true);
    NK_TEST__ACTUAL_BOOL(nk_string__is_equal(&input.array, &output.array));
}

static void
test__simple__parse_command_line_feed(void)
{
    struct terminal_descriptor terminal;
    int terminal_context = 4;
    int command_context = 8;
    struct working_buffer
        NK_STRING__BUCKET_T(500)
    working_buffer = NK_STRING__BUCKET_INITIALIZER_EMPTY(&working_buffer);
    struct error_message
        NK_STRING__BUCKET_T(500)
    error_message = NK_STRING__BUCKET_INITIALIZER_EMPTY(&error_message);
    struct input
        NK_STRING__BUCKET_T(500)
    input = NK_STRING__BUCKET_INITIALIZER(&input, "command\n");
    struct output
        NK_STRING__BUCKET_T(500)
    output = NK_STRING__BUCKET_INITIALIZER_EMPTY(&output);
    struct
        NK_STRING__BUCKET_T(100)
    command_id = NK_STRING__BUCKET_INITIALIZER(&command_id, "command");
    const struct terminal__command_descriptor command_1 = { .command_id = &command_id.array, .interpreter = { .fn =
                    simple__command_function, .command_context = &command_context } };
    simple__terminal_commands.array.items[0] = &command_1;
    simple__terminal_commands.array.length = 1;
    terminal__init(&terminal, &simple__terminal_commands.array, &working_buffer.array, &error_message.array);
    terminal__set_terminal_context(&terminal, &terminal_context);
    terminal__interpret(&terminal, &input.array, &output.array);
    NK_TEST__EXPECT_INT(14);
    NK_TEST__ACTUAL_INT(terminal_context);
    NK_TEST__EXPECT_INT(19);
    NK_TEST__ACTUAL_INT(command_context);
    NK_TEST__EXPECT_BOOL(true);
    NK_TEST__ACTUAL_BOOL(nk_string__is_equal_literal(&output.array, NK_STRING__LITERAL("command\ntest output")));
}

static void
test__simple__parse_partial_command_no_enter(void)
{
    struct terminal_descriptor terminal;
    int terminal_context = 4;
    int command_context = 8;
    struct working_buffer
        NK_STRING__BUCKET_T(500)
    working_buffer = NK_STRING__BUCKET_INITIALIZER_EMPTY(&working_buffer);
    struct error_message
        NK_STRING__BUCKET_T(500)
    error_message = NK_STRING__BUCKET_INITIALIZER_EMPTY(&error_message);
    struct input
        NK_STRING__BUCKET_T(500)
    input = NK_STRING__BUCKET_INITIALIZER(&input, "comm");
    struct output
        NK_STRING__BUCKET_T(500)
    output = NK_STRING__BUCKET_INITIALIZER_EMPTY(&output);
    struct
        NK_STRING__BUCKET_T(100)
    command_id = NK_STRING__BUCKET_INITIALIZER(&command_id, "command");
    const struct terminal__command_descriptor command_1 = { .command_id = &command_id.array, .interpreter = { .fn =
                    simple__command_function, .command_context = &command_context } };
    simple__terminal_commands.array.items[0] = &command_1;
    simple__terminal_commands.array.length = 1;
    terminal__init(&terminal, &simple__terminal_commands.array, &working_buffer.array, &error_message.array);
    terminal__set_terminal_context(&terminal, &terminal_context);
    terminal__interpret(&terminal, &input.array, &output.array);
    nk_string__clear_all(&input.array);
    nk_string__append_literal(&input.array, NK_STRING__LITERAL("and"));
    terminal__interpret(&terminal, &input.array, &output.array);
    NK_TEST__EXPECT_INT(4);
    NK_TEST__ACTUAL_INT(terminal_context);
    NK_TEST__EXPECT_INT(8);
    NK_TEST__ACTUAL_INT(command_context);
    NK_TEST__EXPECT_BOOL(true);
    NK_TEST__ACTUAL_BOOL(nk_string__is_equal(&input.array, &output.array));
}

static void
test__simple__parse_partial_command_line_feed(void)
{
    struct terminal_descriptor terminal;
    int terminal_context = 4;
    int command_context = 8;
    struct working_buffer
        NK_STRING__BUCKET_T(500)
    working_buffer = NK_STRING__BUCKET_INITIALIZER_EMPTY(&working_buffer);
    struct error_message
        NK_STRING__BUCKET_T(500)
    error_message = NK_STRING__BUCKET_INITIALIZER_EMPTY(&error_message);
    struct input
        NK_STRING__BUCKET_T(500)
    input = NK_STRING__BUCKET_INITIALIZER(&input, "comm");
    struct output
        NK_STRING__BUCKET_T(500)
    output = NK_STRING__BUCKET_INITIALIZER_EMPTY(&output);
    struct
        NK_STRING__BUCKET_T(100)
    command_id = NK_STRING__BUCKET_INITIALIZER(&command_id, "command");
    const struct terminal__command_descriptor command_1 = { .command_id = &command_id.array, .interpreter = { .fn =
                    simple__command_function, .command_context = &command_context } };
    simple__terminal_commands.array.items[0] = &command_1;
    simple__terminal_commands.array.length = 1;
    terminal__init(&terminal, &simple__terminal_commands.array, &working_buffer.array, &error_message.array);
    terminal__set_terminal_context(&terminal, &terminal_context);
    terminal__interpret(&terminal, &input.array, &output.array);
    nk_string__clear_all(&input.array);
    nk_string__append_literal(&input.array, NK_STRING__LITERAL("and\n"));
    terminal__interpret(&terminal, &input.array, &output.array);
    NK_TEST__EXPECT_INT(14);
    NK_TEST__ACTUAL_INT(terminal_context);
    NK_TEST__EXPECT_INT(19);
    NK_TEST__ACTUAL_INT(command_context);
    NK_TEST__EXPECT_BOOL(true);
    NK_TEST__ACTUAL_BOOL(nk_string__is_equal_literal(&output.array, NK_STRING__LITERAL("and\ntest output")));
}

static void
test__simple__parse_two_commands_line_feed(void)
{
    struct terminal_descriptor terminal;
    int terminal_context = 4;
    int command_context = 8;
    struct working_buffer
        NK_STRING__BUCKET_T(500)
    working_buffer = NK_STRING__BUCKET_INITIALIZER_EMPTY(&working_buffer);
    struct error_message
        NK_STRING__BUCKET_T(500)
    error_message = NK_STRING__BUCKET_INITIALIZER_EMPTY(&error_message);
    struct input
        NK_STRING__BUCKET_T(500)
    input = NK_STRING__BUCKET_INITIALIZER(&input, "command\ncommand\n");
    struct output
        NK_STRING__BUCKET_T(500)
    output = NK_STRING__BUCKET_INITIALIZER_EMPTY(&output);
    struct
        NK_STRING__BUCKET_T(100)
    command_id = NK_STRING__BUCKET_INITIALIZER(&command_id, "command");
    const struct terminal__command_descriptor command_1 = { .command_id = &command_id.array, .interpreter = { .fn =
                    simple__command_function, .command_context = &command_context } };
    simple__terminal_commands.array.items[0] = &command_1;
    simple__terminal_commands.array.length = 1;
    terminal__init(&terminal, &simple__terminal_commands.array, &working_buffer.array, &error_message.array);
    terminal__set_terminal_context(&terminal, &terminal_context);
    terminal__interpret(&terminal, &input.array, &output.array);
    NK_TEST__EXPECT_INT(24);
    NK_TEST__ACTUAL_INT(terminal_context);
    NK_TEST__EXPECT_INT(30);
    NK_TEST__ACTUAL_INT(command_context);
    NK_TEST__EXPECT_BOOL(true);
    NK_TEST__ACTUAL_BOOL(nk_string__is_equal_literal(&output.array,
                                                     NK_STRING__LITERAL("command\ncommand\ntest outputtest output")));
}

static void
test__simple__parse_multiple_line_feed(void)
{
    struct terminal_descriptor terminal;
    int terminal_context = 4;
    int command_context = 8;
    struct working_buffer
        NK_STRING__BUCKET_T(500)
    working_buffer = NK_STRING__BUCKET_INITIALIZER_EMPTY(&working_buffer);
    struct error_message
        NK_STRING__BUCKET_T(500)
    error_message = NK_STRING__BUCKET_INITIALIZER_EMPTY(&error_message);
    struct input
        NK_STRING__BUCKET_T(500)
    input = NK_STRING__BUCKET_INITIALIZER(&input, "\n\n\n\n\ncommand\n\n\n");
    struct output
        NK_STRING__BUCKET_T(500)
    output = NK_STRING__BUCKET_INITIALIZER_EMPTY(&output);
    struct
        NK_STRING__BUCKET_T(100)
    command_id = NK_STRING__BUCKET_INITIALIZER(&command_id, "command");
    const struct terminal__command_descriptor command_1 = { .command_id = &command_id.array, .interpreter = { .fn =
                    simple__command_function, .command_context = &command_context } };
    simple__terminal_commands.array.items[0] = &command_1;
    simple__terminal_commands.array.length = 1;
    terminal__init(&terminal, &simple__terminal_commands.array, &working_buffer.array, &error_message.array);
    terminal__set_terminal_context(&terminal, &terminal_context);
    terminal__interpret(&terminal, &input.array, &output.array);
    NK_TEST__EXPECT_INT(14);
    NK_TEST__ACTUAL_INT(terminal_context);
    NK_TEST__EXPECT_INT(19);
    NK_TEST__ACTUAL_INT(command_context);
    NK_TEST__EXPECT_BOOL(true);
    NK_TEST__ACTUAL_BOOL(nk_string__is_equal_literal(&output.array,
                                                     NK_STRING__LITERAL("\n\n\n\n\ncommand\n\n\ntest output")));
}

static void
test__simple__parse_command_rn(void)
{
    struct terminal_descriptor terminal;
    int terminal_context = 4;
    int command_context = 8;
    struct working_buffer
        NK_STRING__BUCKET_T(500)
    working_buffer = NK_STRING__BUCKET_INITIALIZER_EMPTY(&working_buffer);
    struct error_message
        NK_STRING__BUCKET_T(500)
    error_message = NK_STRING__BUCKET_INITIALIZER_EMPTY(&error_message);
    struct input
        NK_STRING__BUCKET_T(500)
    input = NK_STRING__BUCKET_INITIALIZER(&input, "command\r\n");
    struct output
        NK_STRING__BUCKET_T(500)
    output = NK_STRING__BUCKET_INITIALIZER_EMPTY(&output);
    struct
        NK_STRING__BUCKET_T(100)
    command_id = NK_STRING__BUCKET_INITIALIZER(&command_id, "command");
    const struct terminal__command_descriptor command_1 = { .command_id = &command_id.array, .interpreter = { .fn =
                    simple__command_function, .command_context = &command_context } };
    simple__terminal_commands.array.items[0] = &command_1;
    simple__terminal_commands.array.length = 1;
    terminal__init(&terminal, &simple__terminal_commands.array, &working_buffer.array, &error_message.array);
    terminal__set_terminal_context(&terminal, &terminal_context);
    terminal__interpret(&terminal, &input.array, &output.array);
    NK_TEST__EXPECT_INT(14);
    NK_TEST__ACTUAL_INT(terminal_context);
    NK_TEST__EXPECT_INT(19);
    NK_TEST__ACTUAL_INT(command_context);
    NK_TEST__EXPECT_BOOL(true);
    NK_TEST__ACTUAL_BOOL(nk_string__is_equal_literal(&output.array, NK_STRING__LITERAL("command\r\ntest output")));
}

static void
test__simple__parse_command_with_args(void)
{
    struct terminal_descriptor terminal;
    int terminal_context = 4;
    int command_context = 8;
    struct working_buffer
        NK_STRING__BUCKET_T(500)
    working_buffer = NK_STRING__BUCKET_INITIALIZER_EMPTY(&working_buffer);
    struct error_message
        NK_STRING__BUCKET_T(500)
    error_message = NK_STRING__BUCKET_INITIALIZER_EMPTY(&error_message);
    struct input
        NK_STRING__BUCKET_T(500)
    input = NK_STRING__BUCKET_INITIALIZER(&input, "command arg1 arg2 2\r\n");
    struct output
        NK_STRING__BUCKET_T(500)
    output = NK_STRING__BUCKET_INITIALIZER_EMPTY(&output);
    struct
        NK_STRING__BUCKET_T(100)
    command_id = NK_STRING__BUCKET_INITIALIZER(&command_id, "command");
    const struct terminal__command_descriptor command_1 = { .command_id = &command_id.array, .interpreter = { .fn =
                    simple__command_function, .command_context = &command_context } };
    simple__terminal_commands.array.items[0] = &command_1;
    simple__terminal_commands.array.length = 1;
    terminal__init(&terminal, &simple__terminal_commands.array, &working_buffer.array, &error_message.array);
    terminal__set_terminal_context(&terminal, &terminal_context);
    terminal__interpret(&terminal, &input.array, &output.array);
    NK_TEST__EXPECT_INT(14);
    NK_TEST__ACTUAL_INT(terminal_context);
    NK_TEST__EXPECT_INT(19);
    NK_TEST__ACTUAL_INT(command_context);
    NK_TEST__EXPECT_BOOL(true);
    NK_TEST__ACTUAL_BOOL(nk_string__is_equal_literal(
            &output.array, NK_STRING__LITERAL("command arg1 arg2 2\r\ntest output arg:arg1 arg:arg2 arg:2")));
}

static void
test__simple__parse_command_with_args_double_space(void)
{
    struct terminal_descriptor terminal;
    int terminal_context = 4;
    int command_context = 8;
    struct working_buffer
        NK_STRING__BUCKET_T(500)
    working_buffer = NK_STRING__BUCKET_INITIALIZER_EMPTY(&working_buffer);
    struct error_message
        NK_STRING__BUCKET_T(500)
    error_message = NK_STRING__BUCKET_INITIALIZER_EMPTY(&error_message);
    struct input
        NK_STRING__BUCKET_T(500)
    input = NK_STRING__BUCKET_INITIALIZER(&input, "command  arg1    arg2  2\r\n");
    struct output
        NK_STRING__BUCKET_T(500)
    output = NK_STRING__BUCKET_INITIALIZER_EMPTY(&output);
    struct
        NK_STRING__BUCKET_T(100)
    command_id = NK_STRING__BUCKET_INITIALIZER(&command_id, "command");
    const struct terminal__command_descriptor command_1 = { .command_id = &command_id.array, .interpreter = { .fn =
                    simple__command_function, .command_context = &command_context } };
    simple__terminal_commands.array.items[0] = &command_1;
    simple__terminal_commands.array.length = 1;
    terminal__init(&terminal, &simple__terminal_commands.array, &working_buffer.array, &error_message.array);
    terminal__set_terminal_context(&terminal, &terminal_context);
    terminal__interpret(&terminal, &input.array, &output.array);
    NK_TEST__EXPECT_INT(14);
    NK_TEST__ACTUAL_INT(terminal_context);
    NK_TEST__EXPECT_INT(19);
    NK_TEST__ACTUAL_INT(command_context);
    NK_TEST__EXPECT_BOOL(true);
    NK_TEST__ACTUAL_BOOL(nk_string__is_equal_literal(
            &output.array, NK_STRING__LITERAL("command  arg1    arg2  2\r\ntest output arg:arg1 arg:arg2 arg:2")));
}


void
test_nk_terminal(void)
{
    static const struct nk_testsuite__test tests[] = {
    NK_TEST__TEST(test__simple__parse_empty),
    NK_TEST__TEST(test__simple__parse_a_letter),
    NK_TEST__TEST(test__simple__parse_command_no_enter),
    NK_TEST__TEST(test__simple__parse_command_line_feed),
    NK_TEST__TEST(test__simple__parse_partial_command_no_enter),
    NK_TEST__TEST(test__simple__parse_partial_command_line_feed),
    NK_TEST__TEST(test__simple__parse_two_commands_line_feed),
    NK_TEST__TEST(test__simple__parse_multiple_line_feed),
    NK_TEST__TEST(test__simple__parse_command_rn),
    NK_TEST__TEST(test__simple__parse_command_with_args),
    NK_TEST__TEST(test__simple__parse_command_with_args_double_space),
    NK_TEST__TEST_TERMINATE() };
    nk_test__run_fixture(tests, NULL, NULL, NK_TESTSUITE__FIXTURE_NAME(none));
}
#else /* !defined(NK_ENABLED_ARRAY) */
void
test_nk_terminal(void)
{
}
#endif /* defined(NK_ENABLED_ARRAY) */
