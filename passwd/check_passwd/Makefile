OBJECT=check_passwd
CC=gcc
FLAGS= -lcrypt

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
	sudo ./$(OBJECT)

.PHONY : clean
clean:
	-rm $(OBJECT)
