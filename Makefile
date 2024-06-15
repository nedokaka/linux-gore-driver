obj-m := gore.o
ccflags-y += -I$(src)
KERNELVERSION = $(shell uname -r)
KERNELDIR = /lib/modules/$(KERNELVERSION)/build

all:
	make -C $(KERNELDIR) M="$(PWD)" modules

clean:
	make -C $(KERNELDIR) M="$(PWD)" clean

install:
	sudo insmod gore.ko

uninstall:
	sudo rmmod gore