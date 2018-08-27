#include "unity.h"
#include "event_handler.h"
#include "reactor.h"
//Do not see the point in mocking the event loop. Must be used to actually test that the reactor does something
#include "reactor_event_loop.h"

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

//Force unity to compile the implementation of reactor interfaces as it does not seem to manage on its own
TEST_FILE("poll_reactor.c")

//Have not found a way for CMock to create mock functions for function pointers
typedef struct {
    Handle handle;
    int value;
    EventHandler event_handler;
} MockData;

//Implementation of eventhandle getHandleFunc
static Handle mock_GetHandleFunc(void *instance)
{
    MockData* data = instance;
    return data->handle;
}

//Implementation of eventhandle handleEventFunc
static void mock_HandleEvent(void *instance)
{
    MockData* data = instance;
    data->value++;
}

static MockData* create_MockData(int initial_value)
{
    int expected_handle = 1;
    int expected_value = 1;
    MockData *data = malloc(sizeof *data);
    data->handle = open("/dev/null", O_RDWR);
    data->value = initial_value;

    data->event_handler.instance = data;
    data->event_handler.get_handle = mock_GetHandleFunc;
    data->event_handler.handle_event = mock_HandleEvent;

    return data;
}

static EventHandler destroy_MockData(MockData* data)
{
    close(data->handle);
    free(data);
}

void test_Reactor_Register()
{
    int initial_value = 0;
    int expected_value = 1;
    MockData* data = create_MockData(initial_value);

    Register(&data->event_handler);

    HandleEvents();

    TEST_ASSERT_EQUAL(expected_value, data->value);

    Unregister(&data->event_handler);
    destroy_MockData(data);
}


void test_Reactor_Deregister()
{
    int initial_value = 0;
    int expected_value = 1;
    MockData* data = create_MockData(initial_value);

    Register(&data->event_handler);

    HandleEvents();

    TEST_ASSERT_EQUAL(expected_value, data->value);

    Unregister(&data->event_handler);

    //Expect this will just timeout and not do anything
    HandleEvents();
    //Ensured that the value has not changed since we have deregistered
    TEST_ASSERT_EQUAL(expected_value, data->value);

    destroy_MockData(data);
}
