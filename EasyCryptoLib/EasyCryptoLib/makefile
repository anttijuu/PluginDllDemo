#
#

IDIR=.
CC=g++

CFLAGS = -c -std=c++11 -fPIC -g -Wall -pthread -I$(IDIR) -DEC_DLL -DEC_DLL_EXPORTS -fvisibility=hidden -fvisibility-inlines-hidden
LFLAGS =  -shared -Wall -fvisibility=hidden -fvisibility-inlines-hidden -o libEasyCrypto.dylib

SOURCES = ./EasyCryptoLib.cpp \
./EasyCryptoPrivMatrix.cpp \
./EasyCryptoPrivReverse.cpp \
./EasyCryptoLibBad.cpp

OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = libEasyCrypto.dylib

all: $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o $@

.cpp.o: *.hpp
	$(CC) $(CFLAGS) $< -o $@

install:
	cp -f libEasyCrypto.dylib /usr/local/lib
	cp -f EasyCryptoLib.hpp /usr/local/include
	cp -f EasyCryptoLibBad.hpp /usr/local/include
	cp -f ECMasterHeader.hpp /usr/local/include

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
	rm -f /usr/local/lib/libEasyCrypto.dylib
	rm -f /usr/local/include/EasyCryptoLib.hpp
	rm -r /usr/local/include/EasyCryptoLibBad.hpp
	rm -r /usr/local/include/ECMasterHeader.hpp

.PHONY:
	all clean

