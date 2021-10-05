SRCS := $(wildcard ./*.c)
OBJC := $(wildcard ./*.o)

compile:
	$(CC) -c $(SRCS) $(CFLAGS)

link:
	$(CC) -o ./target $(OBJC) $(CFLAGS)

prone:
	rm $(OBJC)

all:
	$(CC) -c $(SRCS) $(CFLAGS)
	$(CC) -o ./target $(wildcard ./*.o) $(CFLAGS)
	rm $(OBJC)