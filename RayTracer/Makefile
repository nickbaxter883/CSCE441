CC=g++
CFLAGS=-c -Wall -I/usr/include/GL
LDFLAGS=-L/usr/X11R6/lib -lGL -lGLU -lglut -lm
SOURCES=main.cpp point.cpp shape.cpp tracer.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=rayTracer

all: $(SOURCES) $(EXECUTABLE)
   
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f  $(OBJECTS) $(EXECUTABLE)

