tinyC: y.tab.o lex.yy.o ass6_19CS30005_translator.o ass6_19CS30005_target_translator.o
	g++ -g ass6_19CS30005_translator.o ass6_19CS30005_target_translator.o lex.yy.o y.tab.o -lfl -o tinyC
	@echo "\nMake process successful\nThe binary generated is ./tinyC\nUse command make run for running test files"

lex.yy.c: ass6_19CS30005.l
	flex ass6_19CS30005.l

y.tab.c: ass6_19CS30005.y
	yacc -dtv ass6_19CS30005.y -Wno-empty-rule -Wno-yacc -Wno-conflicts-rr

y.tab.h: ass6_19CS30005.y
	yacc -dtv ass6_19CS30005.y -Wno-empty-rule -Wno-yacc -Wno-conflicts-rr

ass6_19CS30005_target_translator.o: ass6_19CS30005_target_translator.cxx
	g++ -g -c -no-pie ass6_19CS30005_target_translator.cxx
ass6_19CS30005_translator.o: ass6_19CS30005_translator.cxx
	g++ -g -c -no-pie ass6_19CS30005_translator.cxx
lex.yy.o: lex.yy.c
	g++ -g -c -no-pie lex.yy.c
y.tab.o:    y.tab.c
	g++ -g -no-pie -DYYDEBUG -c y.tab.c

libass6_19CS30005.a: ass6_19CS30005.o
	ar -rcs libass6_19CS30005.a ass6_19CS30005.o

ass6_19CS30005.o: ass6_19CS30005.c myl.h
	gcc -g -no-pie -Wall -c ass6_19CS30005.c

clean:
	rm -rf \
	test* \
	lex.yy.c y.tab.h y.output y.tab.c \
	*.o *.s *.a *.out *.gch \
	output-files/* \
	output-bin/* \
	tinyC

ass6_19CS30005.c:
	touch ass6_19CS30005.c

run: libass6_19CS30005.a
	@mkdir -p output-files

	@echo "\nRunning Test Case 1\n"
	./tinyC < input-files/ass6_19CS30005_test1.c > output-files/ass6_19CS30005_quad1.out
	mv output.s output-files/ass6_19CS30005_test1.s
	gcc -g -Wall  -c  output-files/ass6_19CS30005_test1.s -no-pie -o ass6_19CS30005_test1.o
	gcc -g -no-pie ass6_19CS30005_test1.o -o ./output-bin/test1 -L. -lass6_19CS30005

	@echo "\nRunning Test Case 2\n"
	./tinyC < input-files/ass6_19CS30005_test2.c > output-files/ass6_19CS30005_quad2.out
	mv output.s output-files/ass6_19CS30005_test2.s
	gcc -g -Wall  -c  output-files/ass6_19CS30005_test2.s -no-pie -o ass6_19CS30005_test2.o
	gcc -g -no-pie ass6_19CS30005_test2.o -o ./output-bin/test2 -L. -lass6_19CS30005

	@echo "\nRunning Test Case 3\n"
	./tinyC < input-files/ass6_19CS30005_test3.c > output-files/ass6_19CS30005_quad3.out
	mv output.s output-files/ass6_19CS30005_test3.s
	gcc -g -Wall  -c  output-files/ass6_19CS30005_test3.s -no-pie -o ass6_19CS30005_test3.o
	gcc -g -no-pie ass6_19CS30005_test3.o -o ./output-bin/test3 -L. -lass6_19CS30005

	@echo "\nRunning Test Case 4\n"
	./tinyC < input-files/ass6_19CS30005_test4.c > output-files/ass6_19CS30005_quad4.out
	mv output.s output-files/ass6_19CS30005_test4.s
	gcc -g -Wall  -c  output-files/ass6_19CS30005_test4.s -no-pie -o ass6_19CS30005_test4.o
	gcc -g -no-pie ass6_19CS30005_test4.o -o ./output-bin/test4 -L. -lass6_19CS30005

	@echo "\nRunning Test Case 5\n"
	./tinyC < input-files/ass6_19CS30005_test5.c > output-files/ass6_19CS30005_quad5.out
	mv output.s output-files/ass6_19CS30005_test5.s
	gcc -g -Wall  -c  output-files/ass6_19CS30005_test5.s -no-pie -o ass6_19CS30005_test5.o
	gcc -g -no-pie ass6_19CS30005_test5.o -o ./output-bin/test5 -L. -lass6_19CS30005

	@echo "\nAll Binaries for test files can be found in ./output-bin/\nUse command cd output-bin and check the test files."
