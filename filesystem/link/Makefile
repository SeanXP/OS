OBJECT=link unlink symlink readlink
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
	./link ./Makefile ./1akefile
	./symlink ./Makefile ./2akefile
	ls -li *akefile
	./readlink ./2akefile
	./unlink ./1akefile
	./unlink ./2akefile
	ls -li *akefile
	make clean

.PHONY : clean
clean:
	-rm $(OBJECT)
