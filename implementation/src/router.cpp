#include "router.h"

router::router()
{
    neighbors = NULL;

    bufferIncoming = NULL;
    bufferOutgoing = NULL;
    type = ROUTER_TYPE;//default is 2 for router
}
