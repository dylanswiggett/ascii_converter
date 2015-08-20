CFLAGS = -g -Wall -std=c++11
CXX = g++
EXEC_NAME = main
#INCDIRS = -I/usr/include -L/usr/include -I/usr/local/include -L/usr/local/include 
#LIB_DIRS = -L /usr/lib/X11
LINKERS = -lX11 -lm -lpthread
FLAGS = $(CFLAGS) $(LINKERS) $(INCDIRS) $(LIB_DIRS)

all: main.o
	$(CXX) $(CFLAGS) -o $(EXEC_NAME) main.o $(LINKERS)

main.o: main.cpp textcolor.cpp
	$(CXX) $(CFLAGS) -c -o main.o main.cpp

clean:
	rm -f *.o
