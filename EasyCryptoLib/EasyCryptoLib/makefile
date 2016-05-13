IDIR=.
BOOSTDIR=/home/antti/workspace/boost_1_60_0
CC=g++

CFLAGS = -c -std=c++11 -fPIC -g -Wall -pthread -I$(IDIR) -I$(BOOSTDIR)
LFLAGS = -shared -Wall -o libEasyCrypto.so

SOURCES = ./EasyCryptoLibBad.cpp \
./EasyCryptoLib.cpp \
./EasyCryptoPrivMatrix.cpp \
./EasyCryptoPrivReverse.cpp

OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = libEasyCrypto.so

# all: $(OBJECTS) $(EXECUTABLE)
all: $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o $@

.cpp.o: *.hpp
	$(CC) $(CFLAGS) $< -o $@

install:
	cp -f libEasyCrypto.so /usr/lib
	cp -f EasyCryptoLib.hpp /usr/include
	cp -f EasyCryptoLibBad.hpp /usr/include

clean:
	-rm -f $(OBJECTS) $(EXECUTABLE)
 
.PHONY:
	all clean

