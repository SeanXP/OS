OBJECT=$(T1) $(T2) $(T3) $(T4) $(T5) $(T6) $(T7) $(T8)
T1=chdir
T2=pathconf
T3=dir
T4=status
T5=link
T6=unlink
T7=symlink
T8=which

target:$(OBJECT)
$(T1): $(T1).c
	gcc $(T1).c -o $(T1)

clean:
	rm $(OBJECT)

