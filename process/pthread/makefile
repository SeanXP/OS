OBJECT=$(T1) $(T2) 
T1=thread1
T2=thread2

target:$(OBJECT)

$(T1):$(T1).c
	gcc $(T1).c -o $(T1) -lpthread
$(T2):$(T2).c
	gcc $(T2).c -o $(T2) -lpthread

clean:
	rm $(OBJECT)

