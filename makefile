CC=g++
CFLAGS=-c -Wall -std=c++20
LDFLAGS=
SOURCES=main.cpp apply_filter.cpp bmp.cpp filter.cpp read_input.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=ImageEditor

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

read_input.o: read_input.cpp read_input.hpp
	$(CC) $(CFLAGS) read_input.cpp
	
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

apply_filter.o: apply_filter.cpp apply_filter.hpp
	$(CC) $(CFLAGS) apply_filter.cpp

bmp.o: bmp.cpp bmp.hpp
	$(CC) $(CFLAGS) bmp.cpp

filter.o: filter.cpp filter.hpp
	$(CC) $(CFLAGS) filter.cpp

clean:
	rm -rf *o $(EXECUTABLE)
