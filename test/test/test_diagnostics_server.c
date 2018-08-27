//Testing framework
#include "unity.h"
#include "diagnostics_server.h"

//Force unity to compile the implementation of reactor interfaces as it does not seem to manage on its own
TEST_FILE("poll_reactor.c")
TEST_FILE("diagnostics_client.c")
TEST_FILE("tcp_server.c")

void test_DiagnosticsServer_CreateServer()
{
    const unsigned int server_port = 1001;
    DiagnosticsServerPtr server = createServer(server_port);
    TEST_ASSERT_NOT_NULL(server);

    destroyServer(server);
}