IDIR=.
CC=g++

CFLAGS = -c -std=c++11 -fPIC -g -Wall -pthread -I$(IDIR)
LFLAGS = -shared -Wall -o libEasyCrypto.so

SOURCES = ./EasyCryptoLib.cpp \
./EasyCryptoPrivMatrix.cpp \
./EasyCryptoPrivReverse.cpp
./EasyCryptoLibBad.cpp \

OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = libEasyCrypto.so

all: $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o $@

.cpp.o: *.hpp
	$(CC) $(CFLAGS) $< -o $@

install:
	cp -f libEasyCrypto.so /usr/local/lib
	cp -f EasyCryptoLib.hpp /usr/local/include
	cp -f EasyCryptoLibBad.hpp /usr/local/include

clean:
	-rm -f $(OBJECTS) $(EXECUTABLE)
 
.PHONY:
	all clean

