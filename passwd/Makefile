OBJECT=getpwnam getgrnam getpwent
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
	./getpwnam
	./getpwnam $(USER)
	./getgrnam admin
	./getpwent

.PHONY : clean
clean:
	-rm $(OBJECT)
