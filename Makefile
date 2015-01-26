TARGET		:= busexmp loopback
LIBOBJS 	:= buse.o buseOperations.o buseRAMDevice.o buseLODevice.o
OBJS		:= $(TARGET:=.o) $(LIBOBJS)
STATIC_LIB	:= libbuse.a

CC		:= /usr/bin/g++
CFLAGS		:= -g -pedantic -Wall -Wextra
LDFLAGS		:= -L. -lbuse

.PHONY: all clean
all: $(TARGET)

$(TARGET): %: %.o $(STATIC_LIB)
	$(CC) -o $@ $< $(LDFLAGS)
	
$(TARGET:=.o): %.o: %.cpp buse.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(STATIC_LIB): $(LIBOBJS)
	ar rcu $(STATIC_LIB) $(LIBOBJS)

$(LIBOBJS): %.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(TARGET) $(OBJS) $(STATIC_LIB)
