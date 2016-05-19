OBJECT=lseek
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
	./$(OBJECT)
	ls -l *.txt
	du *.txt
	od -c test.txt

.PHONY : clean
clean:
	-rm $(OBJECT) test.txt
