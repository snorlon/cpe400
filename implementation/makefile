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
IP = src/ip.cpp
IPH = src/ip.h

all: main

main: main.o internet.o ip.o hub.o
	$(CC) $(CXXFLAGS) -o $(OUTPUT) main.o internet.o ip.o hub.o $(LIBS)

main.o: $(MAIN) $(INTERNETH) $(IPH) $(HUBH)
	$(CC) $(CXXFLAGS) -c $(MAIN) $(LIBS)

internet.o: $(INTERNET) $(INTERNETH)
	$(CC) $(CXXFLAGS) -c $(INTERNET) $(LIBS)

ip.o: $(IP) $(IPH)
	$(CC) $(CXXFLAGS) -c $(IP) $(LIBS)

hub.o: $(HUB) $(HUBH)
	$(CC) $(CXXFLAGS) -c $(HUB) $(LIBS)

clean:
	rm Project *.o
