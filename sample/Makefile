CC=gcc
CXX=g++
SRCS=step.cc stdin.cc
OBJS=$(SRCS:.cc=.o)
HEADS=$(SRCS:.cc=.h)
TARGETS=$(SRCS:.cc=)
AR=ar
CFLAGS=-I. -g -Wall -I../src
LDFLAGS=-L../lib -lparticle
all: $(TARGETS)

step: $(OBJS)
	$(CXX) -o $@ $@.o $(LDFLAGS)

stdin: $(OBJS)
	$(CXX) -o $@ $@.o $(LDFLAGS)

.cc.o:  $(HEADS) $(SRCS)
	$(CXX) $(CFLAGS) -c $<

clean:
	rm -f *.o *.a *~ *.lo *.la *.so
