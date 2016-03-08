CC=g++
CFLAGS=-c -Wall -I/usr/include/GL -Iinclude
LDFLAGS=-lGL -lGLU -lglut -lglui
SOURCES=robot.cpp model.cpp perspective.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=virus

all: $(SOURCES) $(EXECUTABLE)
   
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@ 

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm -f  $(OBJECTS) $(EXECUTABLE)
