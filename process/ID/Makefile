OBJECT=geteuid setuid
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
test: geteuid
	id
	ls -l ./geteuid
	./geteuid
	sudo chown root ./geteuid
	sudo chmod u+s ./geteuid
	ls -l ./geteuid
	./geteuid
	sudo rm ./geteuid

.PHONY : test2
test2: setuid
	id
	sudo chown root ./setuid
	sudo chmod u+s ./setuid
	ls -l ./setuid
	./setuid
	sudo rm ./setuid

.PHONY : clean
clean:
	-rm $(OBJECT)
