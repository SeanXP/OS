OBJECT=change_hostname
CC=gcc
FLAGS=

.PHONY : TARGET
TARGET:$(OBJECT)

#-------------------------------
$(OBJECT):%:%.c
	$(CC) $< $(FLAGS) -o $@
#-------------------------------

.PHONY : tag
tag:
	ctags -R .

.PHONY : test
test: $(OBJECT)
	make
	sudo ./$(OBJECT) new_hostname_test
	make clean
	bash

.PHONY : restore
restore: $(OBJECT)
	make
	sudo ./$(OBJECT) Aspire-4750
	make clean
	bash


.PHONY : clean
clean:
	-rm $(OBJECT)
