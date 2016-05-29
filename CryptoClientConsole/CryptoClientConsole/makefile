IDIR=.
BOOSTDIR=/home/antti/workspace/boost_1_60_0
CC=g++
LIBS=/usr/lib/libEasyCrypto.so

CFLAGS = -c -std=c++11 -fPIC -g -Wall -pthread -I$(IDIR) -I$(BOOSTDIR)
LFLAGS = -Wall

SOURCES = ./main.cpp

OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = EasyCryptoConsole

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

