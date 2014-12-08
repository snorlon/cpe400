#include "hub.h"
#include "link.h"

netlink::netlink()
{
    start = NULL;
    end = NULL;
    next = NULL;
    weight = 1;//default weight is 1
}

netlink::netlink(hub* nStart, hub* nEnd)
{
    start = nStart;
    end = nEnd;
    next = NULL;
    weight = 1;
}

netlink::~netlink()
{

}
