#  variables 

CFLAGS =-g -Wall -Werror -lm
OFILES = binary_tree.o

#  object file to output file 
bt: $(OFILES)
	gcc $(OFILES) -o bt $(CFLAGS)

#  source file to object file 
binary_tree.o:
	gcc -c binary_tree.c -o binary_tree.o $(CFLAGS)

#  remove temp obj files 
clean:
	rm $(OFILES)






