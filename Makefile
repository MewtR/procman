RM = rm -rf
SRCS = main.c
OBJSC = $(subst .cpp,.o,$(SRCS))
OBJS = $(subst .c,.o,$(OBJSC))
CFLAGS = -g3 # debug with extra information
CXXFLAGS = $(CFLAGS)
CC = $(CXX)

LDLIBS = $(shell pkg-config --libs libprocps)

procman: $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDLIBS)

main.o: main.c 

.PHONY: clean
clean: 
	$(RM) $(OBJS) procman
