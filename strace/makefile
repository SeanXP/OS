OBJECT=$(T1)

T1=hello

traget:$(T1)

$(T1):$(T1).c
	gcc $(T1).c -o $(T1)


clean:
	rm $(T1) $(T1).txt

strace:
	strace -o $(T1).txt	-T -tt -e trace=all ./$(T1)
#	-T				显示每一调用所消耗的时间
#	-t				在输出中的每一行前加上时间信息
#	-tt				在输出中的每一行前加上时间信息，微妙级
#	-ttt			微妙级输出，以秒表示时间
#	-o filename		输出写入到制定文件。
#	-e				制定一个表达式，用来控制如何跟踪
