BIN         := bin
TARGET	    := $(BIN)/buseMainTest
TEST				:= $(BIN)/test
LIBOBJS     := $(BIN)/buse.o $(BIN)/buseOperations.o $(BIN)/buseRAMDevice.o $(BIN)/buseLODevice.o
OBJS		:= $(TARGET:=.o) $(LIBOBJS)
STATIC_LIB	:= $(BIN)/libbuse.a
COMMONHEADERS := commonIncludes.h buse.h

CC    		:= /usr/bin/g++
CFLAGS		:= -pedantic -Wall -Wextra -std=c++14
LDFLAGS		:= -Lbin -lbuse -lboost_system

.PHONY: all clean
all: $(BIN) $(TARGET) $(TEST)

debug: CFLAGS += -DDEBUG -g
debug: $(BIN) $(TARGET) $(TEST)

${BIN}:
	mkdir -p ${BIN}

$(TEST): %: %.o
	$(CC) -o $@ $<

$(TEST:=.o): $(BIN)/%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

$(TARGET): %: %.o $(STATIC_LIB)
	$(CC) -o $@ $< $(LDFLAGS)
	
$(TARGET:=.o): $(BIN)/%.o: %.cpp $(COMMONHEADERS)
	$(CC) $(CFLAGS) -o $@ -c $<

$(STATIC_LIB): $(LIBOBJS)
	ar rcu $(STATIC_LIB) $(LIBOBJS)

$(LIBOBJS): $(BIN)/%.o: %.cpp $(COMMONHEADERS)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(TARGET) $(OBJS) $(STATIC_LIB)
