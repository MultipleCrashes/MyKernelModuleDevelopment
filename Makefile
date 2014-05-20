
obj-m+=hello.o

KDIR=/usr/src/linux-headers-3.11.0-18-generic

all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

