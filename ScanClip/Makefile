CC=g++
CFLAGS=-c -Wall -I/usr/include/GL -Iinclude
LDFLAGS=-L/usr/X11R6/lib -lGL -lGLU -lglut -lm
SOURCES=main.cpp frame.cpp input.cpp clip.cpp scan.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=hw3

all: $(SOURCES) $(EXECUTABLE)
   
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm -f  $(OBJECTS) $(EXECUTABLE)
