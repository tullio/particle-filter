CC=gcc
CXX=g++
all:
	cd src && $(MAKE)

install:
	cp src/libparticle.* lib/

.PHONY: test sample

sample:
	cd sample && $(MAKE)

test:
	cd test && $(MAKE)

clean:
	cd src && $(MAKE) clean
	cd test && $(MAKE) clean
	rm -fR autom4te.cache *~ *.log *.status
	cd lib && rm -f *.a *.so
