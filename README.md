cpe400
======

To run:
    cd implementation
    make clean; make
    ./Project

    Parameters available are:
        DEVICESCOUNT for normal devices
        MASTERCOUNT for master routers
            slaves are automatically generated, 1-6 per master router
        SEED for loading a specific seed for repeated behavior
        CYCLELIMIT for the max number of cycles
        OUTPUTLEVEL for the amount of information to be showed
    
    Parameters must be entered in the order:
        ./Project DEVICESCOUNT MASTERCOUNT SEED CYCLELIMIT OUTPUTLEVEL
    You may omit any parameter and it will default to a usable value, but to omit SEED you must also omit CYCLELIMIT
        The default for SEED is a random seed based on the current time
        The default for CYCLELIMIT is 0, which means it will run infinitely
        The default for OUTPUTLEVEL is 0, which will show everything
            1 shows all but the master-slave-specific information, effectively showing the passage of messages between devices

    An example:
        ./Project 25 5 125923 1000
    
        This will run for 1000 cycles on seed 125923 with 25 normal routers and 5 master routers in addition to that
        Total of 30 routers ignoring the slaves that are automatically generated

    To reduce clutter:
        Run for lower time amounts and observe it, messages may not generate due to being random, but the master-slave interaction is still shown

Recommended executions:
    ./Project 1 20 5 1
        This one will show that the masters each give only one slave a token, and that the slave will transmit but has nothing to transmit yet, forfeiting their token
        Each master that is connected to another master acts like a normal router, yet with the slaves it tells them who may communicate
    ./Project 1 20 5 500000 1
        This is the same demo, but run without showing master-slave for 500,000 cycles
        It will show a single message being generated and that it travels to its destination
        Not shown but occuring is the frame and datagram being rebuilt at each router while the packet is maintained until the destination is reached
    ./Project 1 20 5 5000000 1
        Again, same demo, but running longer for more messages to be shown to show that the program runs successfully and does what it is supposed to do
        Slaves wait their turn and will only operate when given the simulated token, a boolean flag set to true, to transmit
            This increases the transmission time but it still eventually transmits, a few cycles later than it normally would
    
