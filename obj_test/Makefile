
ifneq  ($(KERNELRELEASE),)
obj-m:= kobj_test.o

else
SUBARCH := $(shell uname -m | sed -e s/i.86/i386/ | sed -e s/ppc/powerpc/ | sed -e s/armv.l/arm/)
ARCH ?= $(SUBARCH)
CROSS_COMPILE ?=
KVER  := $(shell uname -r)
KSRC := /lib/modules/$(KVER)/build
# KSRC := /work/kernel

all: modules

modules:
	$(MAKE) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KSRC) M=$(shell pwd)  modules

clean:
	rm *.ko
	rm -fr *.mod.c *.mod *.o .*.cmd *.ko *i
	rm -fr Module.symvers ; rm -fr Module.markers ; rm -fr modules.order
endif
