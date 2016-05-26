OBJECT=mkdir rmdir chdir ls
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
	./mkdir testdir
	./chdir testdir
	./rmdir testdir
	./ls ../
	make clean

.PHONY : clean
clean:
	-rm $(OBJECT)
