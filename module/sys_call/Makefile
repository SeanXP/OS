obj-m := sys_call_test.o

CURRENT_PATH:=$(shell pwd)
VERSION_NUM:=$(shell uname -r)
#LINUX_PATH:=/usr/src/linux-headers-$(VERSION_NUM)
LINUX_PATH:=/usr/src/linux-source-3.2.0

all:
	make -C $(LINUX_PATH) M=$(CURRENT_PATH) modules
clean:
	make -C $(LINUX_PATH) M=$(CURRENT_PATH) clean

