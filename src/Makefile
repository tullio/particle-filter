CC=gcc
CXX=g++
SRCS=particle.cc particles.cc filter.cc
OBJS=$(SRCS:.cc=.o) 
HEADS=$(SRCS:.cc=.h)
TARGETS=libparticle.a
AR=ar
CFLAGS=-I. -g -Wall
all: $(TARGETS)

libparticle.a: $(OBJS)
	$(AR) rv $@ $(OBJS)

.cc.o:  $(HEADS) $(SRCS)
	$(CXX) $(CFLAGS) -c $<

clean:
	rm -f *.o *.a *~ *.lo *.la *.so
