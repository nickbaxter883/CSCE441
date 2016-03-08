CC=g++
CFLAGS=-c -Wall -I/usr/include/GL
LDFLAGS=-L/usr/X11R6/lib -lGL -lGLU -lglut
SOURCES=main.cpp display.cpp mouse.cpp keyboard.cpp menu.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=shapedraw

all: $(SOURCES) $(EXECUTABLE)
   
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm -f  $(OBJECTS) $(EXECUTABLE)
