CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99
LDFLAGS = -lncurses

IFLAGS = -Isrc/visual \
				 -Isrc/runtime \
				 -Isrc/semaphore \
				 -Isrc/listener

SRC = src/main.c \
			src/listener/listener.c \
			src/semaphore/semaphore.c \
			src/runtime/runtime.c \
			src/visual/visual.c

TARGET = danca-das-cadeiras

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(IFLAGS) -o $@ $^ $(LDFLAGS)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)
