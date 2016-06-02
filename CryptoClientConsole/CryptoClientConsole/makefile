IDIR=.
CC=g++
LIBS=/usr/local/lib/libEasyCrypto.so

CFLAGS = -c -std=c++11 -fPIC -g -Wall -pthread -I$(IDIR)
LFLAGS = -Wall

SOURCES = ./main.cpp

OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = EasyCryptoConsole

all: $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) $(LIBS) -o $@

.cpp.o: *.hpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm -f $(OBJECTS) $(EXECUTABLE)
 
.PHONY:
	all clean

