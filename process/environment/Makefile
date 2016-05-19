OBJECT=environ getenv putenv
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
	./getenv HOME LANG PATH PWD SHELL TERM
	./environ
	./putenv

.PHONY : clean
clean:
	-rm $(OBJECT)
