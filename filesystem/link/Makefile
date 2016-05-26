OBJECT=link unlink
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
	./link ./Makefile ./akefile
	ls -li *akefile
	./unlink ./akefile
	ls -li *akefile
	make clean

.PHONY : clean
clean:
	-rm $(OBJECT)
