
obj-m+=hello.o
obj-m+=harishDevice.o
KDIR=/usr/src/linux-headers-3.11.0-18-generic

all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

