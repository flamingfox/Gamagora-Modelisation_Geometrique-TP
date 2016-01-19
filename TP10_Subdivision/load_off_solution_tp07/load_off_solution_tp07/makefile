
CC=g++
CFLAGS=-W -Wall -ansi
LDFLAGS=  -lglut -lm
EXEC=exemple

all: $(EXEC)

$(EXEC): $(EXEC).o
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o
