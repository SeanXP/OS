OBJECT=image1 image2
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
	ls -l $(OBJECT)
	size $(OBJECT)

.PHONY : clean
clean:
	-rm $(OBJECT)
