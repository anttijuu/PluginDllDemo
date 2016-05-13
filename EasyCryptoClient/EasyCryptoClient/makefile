IDIR=.
BOOSTDIR=/home/antti/workspace/boost_1_60_0
CC=g++
LIBS=/usr/lib/libEasyCrypto.so /usr/lib/libboost_system.so.1.60.0

CFLAGS = -c -std=c++11 -fPIC -g -Wall -pthread -I$(IDIR) -I$(BOOSTDIR)
LFLAGS = -std=c++11 -Wall -lm -ldl -pthread -lpthread

SOURCES = ./main.cpp ./jsoncpp.cpp

OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = EasyCryptoClient

# all: $(OBJECTS) $(EXECUTABLE)
all: $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) $(LIBS) -o $@

.cpp.o: *.hpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm -f $(OBJECTS) $(EXECUTABLE)
 
.PHONY:
	all clean

