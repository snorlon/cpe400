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

all: main

main: main.o internet.o ip.o hub.o switch.o router.o
	$(CC) $(CXXFLAGS) -o $(OUTPUT) main.o internet.o ip.o hub.o switch.o router.o $(LIBS)

main.o: $(MAIN) $(INTERNETH) $(IPH) $(HUBH) $(SWITCHH) $(ROUTERH)
	$(CC) $(CXXFLAGS) -c $(MAIN) $(LIBS)

internet.o: $(INTERNET) $(INTERNETH) $(HUBH) $(SWITCHH) $(ROUTERH)
	$(CC) $(CXXFLAGS) -c $(INTERNET) $(HUBH) $(SWITCHH) $(ROUTERH) $(LIBS)

ip.o: $(IP) $(IPH)
	$(CC) $(CXXFLAGS) -c $(IP) $(LIBS)

hub.o: $(HUB) $(HUBH)
	$(CC) $(CXXFLAGS) -c $(HUB) $(LIBS)

switch.o: $(SWITCH) $(SWITCHH) $(HUBH)
	$(CC) $(CXXFLAGS) -c $(SWITCH) $(LIBS)

router.o: $(ROUTER) $(ROUTERH) $(SWITCHH) $(HUBH)
	$(CC) $(CXXFLAGS) -c $(ROUTER) $(LIBS)

clean:
	rm Project *.o
