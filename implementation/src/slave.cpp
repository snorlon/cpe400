#include "slave.h"

slave::slave()
{
    type = SLAVE_TYPE;
    permittedToTransmit = false;

    id = -1;//default ID

    ipAddress = NULL;

    routingTable = NULL;

    next = NULL;
    parent = NULL;

    //generate our mac address here
    macAddress.generate();
    macAddress.printout();

    //generate some random frequency data
    messageGenThreshold = (rand() % 10000000)+12000000;

    incoming = NULL;
    outgoing = NULL;
}

slave::~slave()
{

}

void slave::processOutgoing()
{
    //act only if given permission to
    if(permittedToTransmit)
    {
        //hub::processOutgoing();
        
        bool processed = false;
        //now try to process the frontmost outgoing message and send it along
        if(outgoing!=NULL)
        {
            //check neighbors for next hop

            //hand it off to the next step in the chain
            link* neighbors = links;
            while(neighbors!=NULL && !processed)
            {
                if((neighbors->end->macAddress) == *(outgoing->destinationMac))
                {
                    //they're next to us, so move the message to them

                    cout<<"Message "<<outgoing->strip()->strip()->id<<" handed to "<<outgoing->destinationMac->printout()<<" from "<<macAddress.printout()<<"!"<<endl;

                    //remove the frame
                    frame* delivery = outgoing;
                    outgoing = outgoing->next;
                    delivery->next = NULL;

                    //send it out
                    neighbors->end->recieveFrame(delivery);

                    //clean up
                    processed = true;
                }
                //else
                    //cout<<neighbors->end->macAddress.printout()<<"|"<<ournextHop->printout()<<"|"<<macAddress.printout()<<endl;
                neighbors=neighbors->next;
            }
        }
    }
}

void slave::tick(float dt)
{
    if(permittedToTransmit)
    {
        if(outgoing == NULL)
            cout<<"*Nothing to transmit!"<<endl;
        else
            cout<<"*"<<macAddress.printout()<<" transmitting!"<<endl;
        hub::tick(dt);
    }

    //ensure we always surrender permission when done
    permittedToTransmit = false;
}
