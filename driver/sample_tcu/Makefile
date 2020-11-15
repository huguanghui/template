CROSS_COMPILE ?= mips-linux-gnu-

ISVP_ENV_KERNEL_DIR = /root/SVN/JunZ/T31N_F23_Master/T31N/kernel/trunks/kernel_T31-1.1.1-20200508

KDIR := ${ISVP_ENV_KERNEL_DIR}
MODULE_NAME := drv_test

all: modules

.PHONY: modules clean

$(MODULE_NAME)-objs := t_drv.o
obj-m := $(MODULE_NAME).o

modules:
	@$(MAKE) -C $(KDIR) M=$(shell pwd) $@

clean:
	@rm -rf *.o *~ .depend .*.cmd  *.mod.c .tmp_versions *.ko *.symvers modules.order
