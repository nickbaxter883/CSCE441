CC=g++
CFLAGS=-c -Wall -I/usr/include/GL -I/usr/include/SOIL
LDFLAGS=-L/usr/X11R6/lib -lGL -lGLU -lglut -lSOIL -lglui -lm
SOURCES=main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=island

all: $(SOURCES) $(EXECUTABLE)
   
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm -f  $(OBJECTS) $(EXECUTABLE)
