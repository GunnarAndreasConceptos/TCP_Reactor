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
    int num_of_read_events;
    int num_of_timeout_events;
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
    data->num_of_read_events++;
}


//Implementation of eventhandle handleTimeoutFunc
static void mock_HandleTimeout(void *instance)
{
    MockData* data = instance;
    data->num_of_timeout_events++;
}

static MockData* create_MockData(const char* file_device)
{
    int expected_handle = 1;
    int expected_value = 1;
    MockData *data = malloc(sizeof *data);
    data->handle = open(file_device, O_RDWR);
    data->num_of_read_events = 0;
    data->num_of_timeout_events = 0;

    data->event_handler.instance = data;
    data->event_handler.get_handle = mock_GetHandleFunc;
    data->event_handler.handle_event = mock_HandleEvent;
    data->event_handler.handle_timeout_event = mock_HandleTimeout;

    return data;
}

static MockData* create_MockDataReader()
{
    return create_MockData("/dev/null");
}

static MockData* create_MockTimeoutReader()
{
    return create_MockData("/dev/tty0");
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
    MockData* data = create_MockDataReader();

    Register(&data->event_handler);

    HandleEvents();

    TEST_ASSERT_EQUAL(expected_value, data->num_of_read_events);

    Unregister(&data->event_handler);
    destroy_MockData(data);
}

void test_Reactor_ReadEvents()
{
    int initial_value = 0;
    int expected_value = 1;
    MockData* data = create_MockDataReader();

    Register(&data->event_handler);

    HandleEvents();

    TEST_ASSERT_EQUAL(expected_value, data->num_of_read_events);
    
    //Run again. We assume another read has now been done.
    HandleEvents();
    expected_value++;
    TEST_ASSERT_EQUAL(expected_value, data->num_of_read_events);

    Unregister(&data->event_handler);
    destroy_MockData(data);
}

void test_Reactor_Deregister()
{
    int expected_value = 1;
    MockData* data = create_MockDataReader();

    Register(&data->event_handler);

    HandleEvents();

    TEST_ASSERT_EQUAL(expected_value, data->num_of_read_events);

    Unregister(&data->event_handler);

    //Expect this will just timeout and not do anything
    HandleEvents();
    //Ensured that the value has not changed since we have deregistered
    TEST_ASSERT_EQUAL(expected_value, data->num_of_read_events);

    destroy_MockData(data);
}

void test_Reactor_TimeoutEvent()
{
    int expected_value = 1;
    MockData* data = create_MockTimeoutReader();

    //We register and see that timeout events do not increment
    Register(&data->event_handler);

    HandleEvents();

    TEST_ASSERT_EQUAL(expected_value, data->num_of_timeout_events);
    
    //Run again. We assume another timeout.
    HandleEvents();
    expected_value++;
    TEST_ASSERT_EQUAL(expected_value, data->num_of_timeout_events);

    //Cleanup
    Unregister(&data->event_handler);
    destroy_MockData(data);
}