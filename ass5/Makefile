test: a.out
	
	./a.out < ass5_19CS10065_test1.c > ass5_19CS10065_quads1.out
	@echo "Test File 1 Successfully Translated !\n"


	./a.out < ass5_19CS10065_test2.c > ass5_19CS10065_quads2.out
	@echo "Test File 2 Successfully Translated !\n"
	

	./a.out < ass5_19CS10065_test3.c > ass5_19CS10065_quads3.out
	@echo "Test File 3 Successfully Translated !\n"
	

	./a.out < ass5_19CS10065_test4.c > ass5_19CS10065_quads4.out
	@echo "Test File 4 Successfully Translated !\n"
	

	./a.out < ass5_19CS10065_test5.c > ass5_19CS10065_quads5.out
	@echo "Test File 5 Successfully Translated !\n"


a.out: lex.yy.o ass5_19CS10065.tab.o ass5_19CS10065_translator.o
	g++ lex.yy.o ass5_19CS10065.tab.o ass5_19CS10065_translator.o -lfl

ass5_19CS10065_translator.o: ass5_19CS10065_translator.cxx ass5_19CS10065_translator.h
	g++ -c ass5_19CS10065_translator.h
	g++ -c ass5_19CS10065_translator.cxx

lex.yy.o: lex.yy.c
	g++ -c lex.yy.c

ass5_19CS10065.tab.o: ass5_19CS10065.tab.c
	g++ -c ass5_19CS10065.tab.c

lex.yy.c: ass5_19CS10065.l ass5_19CS10065.tab.h ass5_19CS10065_translator.h
	flex ass5_19CS10065.l

ass5_19CS10065.tab.c: ass5_19CS10065.y
	bison -dtv ass5_19CS10065.y -W

ass5_19CS10065.tab.h: ass5_19CS10065.y
	bison -dtv ass5_19CS10065.y -W
