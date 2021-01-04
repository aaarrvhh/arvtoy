# Makefile: A standard Makefile for helloworld.c

obj = helloworld.o
target = arvhelloworld

all: $(obj)
	${CC} $(obj) -o $(target)

%.o:%.c
	${CC} -c $^ -o $@

.PHONY: clean
clean:
	rm -rf $(obj) $(target)

#all: helloworld

#clean:
#   rm -f helloworld *.o