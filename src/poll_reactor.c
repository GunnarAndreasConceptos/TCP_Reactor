#include "reactor.h"
#include "reactor_event_loop.h"

#include <stddef.h>
#include <poll.h>
#include <stdio.h>
#include <assert.h>

#define MAX_NO_OF_HANDLES 32

#ifndef INFTIM
#define INFTIM -1
#endif

typedef struct
{
    int is_used;
    EventHandler handler;
    struct pollfd fd;
} HandlerRegistration;

static HandlerRegistration registered_handlers[MAX_NO_OF_HANDLES];

static int addToRegistry(EventHandler* handler);
static int removeFromRegistry(EventHandler *handler);

/* We copy all registered event handlers to a poll array */
static size_t buildPollArray(struct pollfd* fds);

static EventHandler* findHandler(int fd);

/* Detect all signalled handles and invoke their corresponding event handlers. */
static void dispatchSignalledHandles(const struct pollfd* fds, size_t no_of_handles);

//Interface implementations
void Register(EventHandler* handler)
{
    assert(NULL != handler);

    if (!addToRegistry(handler))
    {
        printf("No more registrations possible\n");
    }
}

void Unregister(EventHandler* handler)
{
    assert(NULL != handler);

    if (!removeFromRegistry(handler))
    {
        printf("Handler not registered\n");
    }
}

void HandleEvents(void)
{
    struct pollfd fds[MAX_NO_OF_HANDLES] = {0};

    const size_t no_of_handles = buildPollArray(fds);

    //Workaround for testing deregistering. May be better to just add a timeout?
    if (no_of_handles == 0)
    {
        return;
    }

    if (0 < poll(fds, no_of_handles, INFTIM))
    {
        dispatchSignalledHandles(fds, no_of_handles);
    }
    else
    {
        printf("Poll failure");
    }
}

//local functions
static int addToRegistry(EventHandler* handler)
{
    int is_registered = 0;
    int i = 0;

    for (i = 0; (i < MAX_NO_OF_HANDLES) && (0 == is_registered); i++)
    {
        //We find a free position
        if (0 == registered_handlers[i].is_used)
        {
            HandlerRegistration* free_entry = &registered_handlers[i];

            free_entry->handler = *handler;
            free_entry->fd.fd = handler->get_handle(handler->instance);
            free_entry->fd.events = POLLIN;

            is_registered = free_entry->is_used = 1;

            printf("Reactor: Added handle with ID = %d\n", free_entry->fd.fd);
        }
    }

    return is_registered;
}

static int removeFromRegistry(EventHandler* handler)
{
    int i = 0;
    int node_removed = 0;

    for (i = 0; (i < MAX_NO_OF_HANDLES) && (0 == node_removed); i++)
    {
        if (registered_handlers[i].is_used && 
        registered_handlers[i].handler.instance == handler->instance)
        {
            registered_handlers[i].is_used = 0;
            node_removed = 1;
            printf("Reactor: Removed event handler with ID = %d\n", registered_handlers[i].fd.fd);
        }
    }
    return node_removed;
}

static size_t buildPollArray(struct pollfd* fds)
{
    int i = 0;
    size_t no_of_copied_handles = 0;

    for (i = 0; i < MAX_NO_OF_HANDLES; i++)
    {
        if (registered_handlers[i].is_used)
        {
            fds[no_of_copied_handles] = registered_handlers[i].fd;
            ++no_of_copied_handles;
        }
    }
    return no_of_copied_handles;
}

static EventHandler * findHandler(int fd)
{
    EventHandler* matching_handler = NULL;
    int i = 0;

    for (i = 0; (i < MAX_NO_OF_HANDLES) && (NULL == matching_handler); ++i)
    {
        if (registered_handlers[i].is_used &&
        (registered_handlers[i].fd.fd == fd))
        {
            matching_handler = &registered_handlers[i].handler;
        }
    }
    return matching_handler;
}

static void dispatchSignalledHandles(const struct pollfd *fds, size_t no_of_handles)
{
    size_t i = 0;

    for (i = 0; i < no_of_handles; ++i)
    {
        if ((POLLIN | POLLERR) & fds[i].revents)
        {
            EventHandler* signalled_handler = findHandler(fds[i].fd);
            
            if (NULL != signalled_handler)
            {
                signalled_handler->handle_event(signalled_handler->instance);
            }
        }
    }
}