MAIN	= main.o mini_string.o mini_memory.o mini_io.o
TOUCH	= mini_touch.o mini_string.o mini_memory.o mini_io.o
CP = mini_cp.o mini_string.o mini_memory.o mini_io.o
ECHO = mini_echo.o mini_string.o mini_memory.o mini_io.o
CAT = mini_cat.o mini_string.o mini_memory.o mini_io.o
SOURCE	= main.c mini_string.c mini_memory.c mini_io.c mini_touch.c mini_cp.c mini_cat.c mini_shell.c
HEAD = mini_head.o mini_string.o mini_memory.o mini_io.o
TAIL = mini_tail.o mini_string.o mini_memory.o mini_io.o
CLEAN = mini_clean.o mini_string.o mini_memory.o mini_io.o
GREP = mini_grep.o mini_string.o mini_memory.o mini_io.o
MINISHELL = mini_shell.o mini_string.o mini_memory.o mini_io.o
WC = wc.o mini_string.o mini_memory.o mini_io.o
HEADER	= mini_lib.h 
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(MAIN)
	$(CC) -g -Wall $(MAIN) -o main $(LFLAGS)

touch: $(TOUCH)
	$(CC) -g -Wall $(TOUCH) -o mini_touch $(LFLAGS)

mini_touch.o: mini_touch.c
	$(CC) $(FLAGS) mini_touch.c

mini_shell: $(MINISHELL)
	$(CC) -g -Wall $(MINISHELL) -o mini_shell $(LFLAGS)

mini_shell.o: mini_shell.c
	$(CC) $(FLAGS) mini_shell.c

cat: $(CAT)
	$(CC) -g -Wall $(CAT) -o mini_cat $(LFLAGS)

mini_cat.o: mini_cat.c
	$(CC) $(FLAGS) mini_cat.c


cp: $(CP)
	$(CC) -g -Wall $(CP) -o mini_cp $(LFLAGS)

echo: $(ECHO)
	$(CC) -g -Wall $(ECHO) -o mini_echo $(LFLAGS)

mini_echo.o: mini_echo.c
	$(CC) $(FLAGS) mini_echo.c

head: $(HEAD)
	$(CC) -g -Wall $(HEAD) -o mini_head $(LFLAGS)

mini_head.o: mini_head.c
	$(CC) $(FLAGS) mini_head.c

tail: $(TAIL)
	$(CC) -g -Wall $(TAIL) -o mini_tail $(LFLAGS)

mini_tail.o: mini_tail.c
	$(CC) $(FLAGS) mini_tail.c

clean: $(CLEAN)
	$(CC) -g -Wall $(CLEAN) -o mini_clean $(LFLAGS)

mini_clean.o: mini_clean.c
	$(CC) $(FLAGS) mini_clean.c

grep: $(GREP)
	$(CC) -g -Wall $(GREP) -o mini_grep $(LFLAGS)

mini_grep.o: mini_grep.c
	$(CC) $(FLAGS) mini_grep.c

wc: $(WC)
	$(CC) -g -Wall $(WC) -o wc $(LFLAGS)

wc.o: wc.c
	$(CC) $(FLAGS) wc.c

mini_cp.o: mini_cp.c
	$(CC) $(FLAGS) mini_cp.c

main.o: main.c
	$(CC) $(FLAGS) main.c

mini_string.o: mini_string.c
	$(CC) $(FLAGS) mini_string.c 

mini_memory.o: mini_memory.c
	$(CC) $(FLAGS) mini_memory.c 

mini_io.o: mini_io.c
	$(CC) $(FLAGS) mini_io.c 

cleano:
	rm -f *.o

cleanprog:
	rm main mini_cp mini_cat mini_echo mini_touch mini_clean mini_grep mini_head mini_tail wc mini_shell