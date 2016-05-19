OBJECT=dup dup2
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
test:$(OBJECT)
	./dup
test2:$(OBJECT)
	./dup2

.PHONY : clean
clean:
	-rm $(OBJECT) ./*.txt
