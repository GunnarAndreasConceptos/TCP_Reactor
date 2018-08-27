#include "@@@@poll_reactor.c"
#include "../src/poll_reactor.c"
#include "build/temp/_test_reactor.c"
#include "reactor_event_loop.h"
#include "reactor.h"
#include "event_handler.h"
#include "unity.h"


















typedef struct {

    Handle handle;

    int value;

    EventHandler event_handler;

} MockData;





static Handle mock_GetHandleFunc(void *instance)

{

    MockData* data = instance;

    return data->handle;

}





static void mock_HandleEvent(void *instance)

{

    MockData* data = instance;

    data->value++;

}



static MockData* create_MockData(int initial_value)

{

    int expected_handle = 1;

    int expected_value = 1;

    MockData *data = malloc(sizeof data);

    data->handle = open("/dev/null", 

                                    02

                                          );

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



    UnityAssertEqualNumber((UNITY_INT)((expected_value)), (UNITY_INT)((data->value)), (

   ((void *)0)

   ), (UNITY_UINT)(69), UNITY_DISPLAY_STYLE_INT);



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



    UnityAssertEqualNumber((UNITY_INT)((expected_value)), (UNITY_INT)((data->value)), (

   ((void *)0)

   ), (UNITY_UINT)(86), UNITY_DISPLAY_STYLE_INT);



    Unregister(&data->event_handler);





    HandleEvents();



    UnityAssertEqualNumber((UNITY_INT)((expected_value)), (UNITY_INT)((data->value)), (

   ((void *)0)

   ), (UNITY_UINT)(93), UNITY_DISPLAY_STYLE_INT);



    destroy_MockData(data);

}
