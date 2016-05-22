OBJECT=date broken-down-time
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
	./date
	./broken-down-time

.PHONY : clean
clean:
	-rm $(OBJECT)
