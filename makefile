CC = gcc
CFLAGS = -O2 -Wall -Wextra
DEBUG_FLAGS = -g -fsanitize=address
DEBUG = FALSE


%.o: %.c
	ifeq ($(DEBUG), TRUE)
		$(CC) $(CFLAGS) $(DEBUG_FLAGS) -c $^ -o $@
	else
		$(CC) $(CFLAGS) -c $^ -o $@
	endif


clean:
	rm -f *.o

