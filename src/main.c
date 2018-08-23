#include "diagnostics_server.h"

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    const unsigned int server_port = 1001;
    DiagnosticsServerPtr server = createServer(server_port);

    if (NULL == server)
    {
        printf("Failed to create the server");
        exit(EXIT_FAILURE);
    }
    return;
}