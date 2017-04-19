IDIR=.
SYSDIR=/usr/local/include
CC=g++
LIBS=/usr/local/lib/libEasyCrypto.dylib /usr/local/lib/libboost_system.dylib

CFLAGS = -c -std=c++11 -fPIC -g -Wall -pthread -I$(IDIR) -I$(SYSDIR)
LFLAGS = -std=c++11 -Wall -lm -ldl -pthread -lpthread

SOURCES = ./main.cpp ./CryptoServer.cpp ./jsoncpp.cpp

OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = EasyCryptoServer

all: $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) $(LIBS) -o $@

.cpp.o: *.hpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm -f $(OBJECTS) $(EXECUTABLE)
 
.PHONY:
	all clean

