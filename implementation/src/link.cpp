#include "hub.h"
#include "link.h"

link::link()
{
    start = NULL;
    end = NULL;
    next = NULL;
    weight = 1;//default weight is 1
}

link::link(hub* nStart, hub* nEnd)
{
    start = nStart;
    end = nEnd;
    next = NULL;
    weight = 1;
}

link::~link()
{

}
