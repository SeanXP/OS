OBJECT=sysconf pathconf
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
	./sysconf
	./pathconf

.PHONY : clean
clean:
	-rm $(OBJECT)
