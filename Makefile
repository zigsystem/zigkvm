
override CXXFLAGS += -std=c++14 $(shell pkg-config --cflags libuvc libvncserver)
override LDLIBS += -std=c++14  $(shell pkg-config --libs  libuvc libvncserver) -pthread -lboost_filesystem
CC=${CXX}

all: zigkvm

zigkvm: keymapping.o zigkvm.o usbgadget.o

clean:
	rm -rf zigkvm *.o

.PHONY: zigkvm.cpp
