OBJECT=readv writev
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
test:
	make
	./writev
	ls -l test.dat
	cat test.dat
	od test.dat
	./readv

.PHONY : clean
clean:
	-rm $(OBJECT) test.dat
