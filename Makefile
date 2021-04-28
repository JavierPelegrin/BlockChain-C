CC=gcc
EXEC=Project
OBJS=main.o BlockChain.o sha256.o sha256_utils.o mine.o transaction.o queue.o
INCS=./inc
CFLAGS=-std=c99 -lm -Wextra -Wall -Werror -pedantic -I$(INCS)

ifeq ($(DEBUG),yes)
	CFLAGS += -g
	LDFLAGS +=
endif

$(EXEC) : ./obj/$(OBJS)
	@$(CC) $(CFLAGS) $^ -o ./bin/$@
	@mv *.o ./obj

./obj/%.o : %.c
	@mkdir -p bin obj
	@$(CC) -c $(CFLAGS) $< -o $@

main.o : $(OBJS)

clean:
	rm -fr ./obj/*.o ./bin/$(EXEC)
clear:
	rm -fr $(EXEC)
