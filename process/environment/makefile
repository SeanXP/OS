OBJECT=environ getenv

target:$(OBJECT)

environ:environ.c
	gcc environ.c -o environ
getenv: getenv.c
	gcc getenv.c -o getenv

test:getenv
	./getenv HOME LANG PATH PWD SHELL TERM
clean:
	rm $(OBJECT)
	
