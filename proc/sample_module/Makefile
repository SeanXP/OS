obj-m := sample.o

CURRENT_PATH:=$(shell pwd)
VERSION_NUM:=$(shell uname -r)
LINUX_PATH:=/usr/src/linux-headers-$(VERSION_NUM)

all:
	make -C $(LINUX_PATH) M=$(CURRENT_PATH) modules
clean:
	make -C $(LINUX_PATH) M=$(CURRENT_PATH) clean
test:
	make
	sudo insmod sample.ko
	cat /proc/proc_test/current
	head /proc/proc_test/current_too
	cat /proc/proc_test/hello
	sudo rmmod sample
	make clean
test2:
	make 
	sudo insmod sample.ko
	ls -l /proc/12345678
	cat /proc/12345678/hello
	head /proc/12345678/hello
	cat /proc/12345678/world
	sudo rmmod sample
	make clean
