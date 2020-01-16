CC	= gcc
RM	= rm



clean:
	${RM}	standard_test standard_test.o Cbuf16.o

standard_test:		standard_test.o Cbuf16.o 
	${CC}  -o standard_test standard_test.o  Cbuf16.o 

margin_test:	margin_test.o Cbuf16_margin.o
	${CC}	-o margin_test margin_test.o Cbuf16_margin.o

Cbuf16.o:	Cbuf16.c Cbuf16.h
	${CC}  -c Cbuf16.c

Cbuf16_margin.o:	Cbuf16_margin.c Cbuf16_margin.h
	${CC}	-c Cbuf16_margin.c

standard_test.o:	standard_test.c
	${CC}	-c standard_test.c

margin_test.o:	margin_test.c
	${CC}	-c margin_test.c
