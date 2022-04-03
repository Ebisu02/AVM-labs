CC=g++
CFLAGS=-c -Wall 
LDFLAGS=-std=gnu++17
SOURCES=main.cpp mySimpleComputer.cpp bc.cpp myTerm.cpp myReadKey.cpp
OBJECTS=$(SOURCES: .cpp=.o)
EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
	
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
