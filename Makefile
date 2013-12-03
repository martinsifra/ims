CC=g++
CFLAGS=-c -Wall
LDFLAGS=  -lsimlib -lm 
SOURCES=main.cpp emailCustomer.cpp streamCustomer.cpp ftpCustomer.cpp hardDisk.cpp Ram.cpp Cpu.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=cloud

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@


clean:
	rm -f *.o cloud

