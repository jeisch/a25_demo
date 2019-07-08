
CC=g++
CFLAGS= -g -Wall -Iinclude/ -I/opt/menlinux/INCLUDE/NATIVE -DVERSION=\"$(GIT_VERSION)\"
LDFLAGS= -lvme4l_api -lrt
SOURCES= src/a25_vme.cc
OBJECTS= $(addprefix obj/,$(notdir $(SOURCES:.cc=.o)))
UTILS= $(wildcard utils/*.cc)
EXECUTABLES= $(addprefix bin/,$(notdir $(patsubst %.cc,%,$(UTILS))))
SHAREDLIBS= lib/liba25_vme.so
GIT_VERSION := $(shell git describe --abbrev=4 --dirty --always --tags)

all: $(EXECUTABLES) $(SHAREDLIBS)
    
bin/%: utils/%.cc $(OBJECTS) 
	mkdir -p bin/
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $< $(OBJECTS) 

obj/%.o: src/%.cc
	mkdir -p obj/
	$(CC) -c -fpic -o $@ $(CFLAGS) $<

lib/lib%.so: obj/%.o
	mkdir -p lib/
	$(CC) -shared -o $@ $<

clean:
	rm -rf $(EXECUTABLES) $(SHAREDLIBS) $(OBJECTS) obj/


