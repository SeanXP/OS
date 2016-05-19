OBJECT=setjmp
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
	./$(OBJECT)
	./$(OBJECT) 2

.PHONY : clean
clean:
	-rm $(OBJECT)
