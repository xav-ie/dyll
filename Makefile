CC=gcc
CFLAGS=-Wall -g
BINS=libplus1.so libplus2.so test.elf

all: $(BINS)

clean:
	rm $(BINS)
	

%.so: %.c
	$(CC) $(CFLAGS) -fPIC -shared -o $@ $^

%.elf: %.c
	$(CC) $(CFLAGS) -o $@ $^ -ldl

