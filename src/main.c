#include "diagnostics_server.h"
#include "reactor_event_loop.h"

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    const unsigned int server_port = 0x5545;
    DiagnosticsServerPtr server = createServer(server_port);

    if (NULL == server)
    {
        printf("Failed to create the server");
        exit(EXIT_FAILURE);
    }

    /* Enter the eternal reactive event loop. */
    while(1)
    {
        HandleEvents();
    }
    return 0;
}