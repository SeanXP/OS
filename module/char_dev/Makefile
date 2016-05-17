obj-m := char_dev.o

CURRENT_PATH:=$(shell pwd)
VERSION_NUM:=$(shell uname -r)
LINUX_PATH:=/usr/src/linux-headers-$(VERSION_NUM)

TARGET:
	make -C $(LINUX_PATH) M=$(CURRENT_PATH) modules
clean:
	make -C $(LINUX_PATH) M=$(CURRENT_PATH) clean
	-rm main
tag:
	ctags -R .

main:	main.c
	gcc	main.c -o main
	@echo "-----------------------读取字符设备的默认值-----------------------"
	sudo ./main read
	@echo "-----------------------给字符设备写入字符串-----------------------"
	sudo ./main write "write what I want to write..."
	@echo "-----------------------再次读取字符设备-----------------------"
	sudo ./main read
	@echo "-----------------------查看内核输出消息-----------------------"
	dmesg | tail
insmod:
	@echo "-----------------------加载字符驱动模块-----------------------"
	sudo insmod char_dev.ko
	dmesg | tail
	@echo "-----------------------创建字符设备节点-----------------------"
	sudo mknod /dev/char_dev c 250 0
	ls -l /dev/char_dev
rmmod:
	@echo "-----------------------卸载字符驱动模块-----------------------"
	sudo rmmod char_dev
	dmesg | tail
	@echo "-----------------------删除字符设备节点-----------------------"
	sudo rm /dev/char_dev
