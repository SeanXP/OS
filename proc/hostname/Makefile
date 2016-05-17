OBJECT=$(T1)
T1=change_hostname

target:$(OBJECT)
$T1:$(T1).c
	gcc $(T1).c -o $(T1)

clean:
	rm $(OBJECT)
test:
	make
	sudo ./$(T1) new_hostname_test
	make clean
	bash
restore:
	make
	sudo ./$(T1) Aspire-4750
	make clean
	bash
