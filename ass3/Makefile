output : a.out ass3_19CS30005_19CS10065_test.c
	./a.out < ass3_19CS30005_19CS10065_test.c > ass3_output_19CS30005_19CS10065.txt

a.out: lex.yy.c
	gcc lex.yy.c -lfl

lex.yy.c: ass3_19CS30005_19CS10065.l
	flex ass3_19CS30005_19CS10065.l ass3_19CS30005_19CS10065.c

clean:
	rm a.out lex.yy.c