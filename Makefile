CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99
LDFLAGS = -lncurses

SRC = src/main.c src/listener/listener.c src/semaphore/semaphore.c src/runtime/runtime.c src/runtime/visual.c
TARGET = danca-das-cadeiras

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(TARGET)
