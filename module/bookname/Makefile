obj-m := bookname.o

CURRENT_PATH:=$(shell pwd)
VERSION_NUM:=$(shell uname -r)
LINUX_PATH:=/usr/src/linux-headers-$(VERSION_NUM)

all:
	make -C $(LINUX_PATH) M=$(CURRENT_PATH) modules
clean:
	make -C $(LINUX_PATH) M=$(CURRENT_PATH) clean
test1:
	sudo insmod bookname.ko 
test2:
	sudo insmod bookname.ko book_name='Goodbook' num=10086
rmmod:
	sudo rmmod bookname
