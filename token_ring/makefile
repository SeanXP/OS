OBJECT=$(T1) $(T2) $(T3)

T1=one_ring
T2=two_ring
T3=n_ring

target:$(OBJECT)

$(T1):$(T1).c
	gcc $(T1).c -o $(T1)
$(T2):$(T2).c
	gcc $(T2).c -o $(T2)
$(T3):$(T3).c
	gcc $(T3).c -o $(T3)

clean:
	rm $(OBJECT)
