#include "diagnostics_server.h"
#include "reactor_event_loop.h"

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#define DEFAULT_PORT 5045

typedef struct
{
    unsigned int port;
} InputOptions;

void printUsage()
{
    printf("Usage: tcp_reactor -p port\n");
}
//Returns -1 on failure
int parseInputOptions(int argc, char *argv[], InputOptions *options)
{
    if (options == NULL)
    {
        return -1;
    }

    const char* valid_option = "p:";
    int num_of_options_parsed = 0;
    int c;

    while((c = getopt(argc, argv, valid_option)) != -1)
    {
        switch (c)
        {
            case 'p':
                options->port = atoi(optarg);
                break;
            default:
                printUsage();
                exit(EXIT_FAILURE);
        }
        num_of_options_parsed++;
    }
    return num_of_options_parsed;
}

int main(int argc, char *argv[])
{
    InputOptions options = {DEFAULT_PORT};
    if (parseInputOptions(argc, argv, &options) == -1)
    {
        printf("Input parsing failure\n");
        exit(EXIT_FAILURE);
    }

    printf("Creating server with port nr %d\n", options.port);

    DiagnosticsServerPtr server = createServer(options.port);

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