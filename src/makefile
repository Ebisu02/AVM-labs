CC=g++
CFLAGS=-c -Wall 
LDFLAGS=-std=gnu++17
SOURCES=src_code/main.cpp src_code/mySimpleComputer.cpp src_code/bc.cpp src_code/myTerm.cpp src_code/myReadKey.cpp src_code/assembler.cpp src_code/msc.cpp
OBJECTS=$(SOURCES: .cpp=.o)
EXECUTABLE=src_code/obj/main

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
	
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

exe:
	-./src_code/obj/main 
	clear
