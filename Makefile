CC=gcc
EXEC=Project
OBJS=main.o BlockChain.o sha256.o sha256_utils.o mine.o transaction.o
INCS=./inc
CFLAGS=-std=c99 -Wextra -Wall -Werror -pedantic -I$(INCS)

ifeq ($(DEBUG),yes)
	CFLAGS += -g
	LDFLAGS +=
endif

$(EXEC) : ./obj/$(OBJS)
	mkdir -p bin obj inc
	@$(CC) $(CFLAGS) $^ -o ./bin/$@
	@mv *.o ./obj

./obj/%.o : %.c
	@$(CC) -c $(CFLAGS) $< -o $@

main.o : $(OBJS)

clean:
	rm -fr ./obj/*.o ./bin/$(EXEC)
clear:
	rm -fr $(EXEC)
