# Linux
CC=g++
LIBS= 

# For Macs uncomment the next line and comment out the previous one
#CC=clang++
#LIBS=  -framework OpenGL -framework GLUT -framework Cocoa -lGLEW -stdlib=libc++
# Assuming you want to use a recent compiler

# Compiler flags
CXXFLAGS= -g -Wall -Wextra -std=c++0x $(DEFS)


OUTPUT = Project
MAIN = src/main.cpp
INTERNET = src/internet.cpp
INTERNETH = src/internet.h
HUB = src/hub.cpp
HUBH = src/hub.h
SWITCH = src/switch.cpp
SWITCHH = src/switch.h
ROUTER = src/router.cpp
ROUTERH = src/router.h
IP = src/ip.cpp
IPH = src/ip.h
IPREG = src/registry.cpp
IPREGH = src/registry.h
MAC = src/mac.cpp
MACH = src/mac.h
LINK = src/link.cpp
LINKH = src/link.h
FRAME = src/frame.cpp
FRAMEH = src/frame.h
DATAGRAM = src/datagram.cpp
DATAGRAMH = src/datagram.h
PACKET = src/packet.cpp
PACKETH = src/packet.h
ROUTING = src/routing.cpp
ROUTINGH = src/routing.h
MASTER = src/master.cpp
MASTERH = src/master.h
SLAVE = src/slave.cpp
SLAVEH = src/slave.h

all: main

main: main.o internet.o ip.o hub.o switch.o router.o link.o mac.o registry.o frame.o datagram.o packet.o routing.o master.o slave.o
	$(CC) $(CXXFLAGS) -o $(OUTPUT) main.o internet.o ip.o hub.o switch.o router.o link.o mac.o registry.o frame.o datagram.o packet.o  routing.o master.o slave.o $(LIBS)

main.o: $(MAIN) $(INTERNETH) $(IPH) $(HUBH) $(SWITCHH) $(ROUTERH)
	$(CC) $(CXXFLAGS) -c $(MAIN) $(LIBS)

internet.o: $(INTERNET) $(INTERNETH) $(HUBH) $(SWITCHH) $(ROUTERH) $(MASTERH) $(SLAVEH) $(IPREGH)
	$(CC) $(CXXFLAGS) -c $(INTERNET) $(LIBS)

ip.o: $(IP) $(IPH) $(IPREGH)
	$(CC) $(CXXFLAGS) -c $(IP) $(LIBS)

registry.o: $(IPREG) $(IPREGH) $(IPH)
	$(CC) $(CXXFLAGS) -c $(IPREG) $(LIBS)

mac.o: $(MAC) $(MACH)
	$(CC) $(CXXFLAGS) -c $(MAC) $(LIBS)

hub.o: $(HUB) $(HUBH) $(LINKH) $(MACH) $(IPH) $(FRAMEH) $(ROUTINGH) $(DATAGRAMH) $(PACKETH)
	$(CC) $(CXXFLAGS) -c $(HUB) $(LIBS)

switch.o: $(SWITCH) $(SWITCHH) $(HUBH)
	$(CC) $(CXXFLAGS) -c $(SWITCH) $(LIBS)

link.o: $(LINK) $(LINKH) $(HUBH)
	$(CC) $(CXXFLAGS) -c $(LINK) $(LIBS)

router.o: $(ROUTER) $(ROUTERH) $(SWITCHH) $(HUBH)
	$(CC) $(CXXFLAGS) -c $(ROUTER) $(LIBS)

frame.o: $(FRAME) $(FRAMEH) $(MACH) $(DATAGRAMH)
	$(CC) $(CXXFLAGS) -c $(FRAME) $(LIBS)

datagram.o: $(DATAGRAM) $(DATAGRAMH) $(IPH) $(PACKETH)
	$(CC) $(CXXFLAGS) -c $(DATAGRAM) $(LIBS)

packet.o: $(PACKET) $(PACKETH) $(IPH)
	$(CC) $(CXXFLAGS) -c $(PACKET) $(LIBS)

routing.o: $(ROUTING) $(ROUTINGH) $(IPH) $(MACH) $(LINKH)
	$(CC) $(CXXFLAGS) -c $(ROUTING) $(LIBS)

master.o: $(MASTER) $(MASTERH) $(SLAVEH) $(HUBH) $(ROUTERH) $(IPH) $(MACH)
	$(CC) $(CXXFLAGS) -c $(MASTER) $(LIBS)

slave.o: $(SLAVE) $(SLAVEH) $(ROUTERH) $(IPH) $(MACH)
	$(CC) $(CXXFLAGS) -c $(SLAVE) $(LIBS)

clean:
	rm Project *.o
