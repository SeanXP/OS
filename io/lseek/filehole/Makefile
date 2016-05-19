OBJECT=filehole
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

.PHONY : clean
clean:
	-rm $(OBJECT) *.txt
