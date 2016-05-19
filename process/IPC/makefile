OBJECT=$(T1) $(T2) $(T3)
T1=peterson
T2=producer-consumer
T3=philosopher

target:$(OBJECT)

$(T1):$(T1).c
	gcc $(T1).c -o $(T1) -lpthread
$(T2):$(T2).c
	gcc $(T2).c -o $(T2) -lpthread
$(T3):$(T3).c
	gcc $(T3).c -o $(T3) -lpthread
		
clean:
	rm $(OBJECT)
