#ifndef ROUTE_H
#define ROUTE_H

#include "pages.h"
#include "controller.h" //Stores all controller headers

void handleRouting(CLIENT *client);

struct Route {
    const char *method;
    const char *path;
    void (*handler)(CLIENT *client);
};

//store routes
extern struct Route routes[];


#endif