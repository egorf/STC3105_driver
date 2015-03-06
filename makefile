CC = g++
CFLAGS = -c -Wall
LDFLAGS = 
SOURCES = example.cpp I2Cdev.cpp STC3105.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = example

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *o $(EXECUTABLE)