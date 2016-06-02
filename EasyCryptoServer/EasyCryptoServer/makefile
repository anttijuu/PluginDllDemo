IDIR=.
BOOSTDIR=/media/antti/workspace/boost_1_60_0
CC=g++
LIBS=/usr/local/lib/libEasyCrypto.so /usr/lib/libboost_system.so.1.60.0

CFLAGS = -c -std=c++11 -fPIC -g -Wall -pthread -I$(IDIR) -I$(BOOSTDIR)
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

