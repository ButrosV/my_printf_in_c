CC=gcc
CFLAGS=-Wall -Wextra -Werror # -g3 -fsanitize=address
DEPS=my_printf.h
TARGET=my_printf
SRCS := $(wildcard *print.c)
OBJS := $(SRCS:.c=.o)

all : $(TARGET)
$(TARGET) : $(OBJS)
	$(info Compiling program '$(TARGET)' from multiple source files: $(SRCS))
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

$(OBJS) : $(SRCS) $(DEPS)
	$(CC) $(CFLAGS) -c $(SRCS)

clean:
	$(info Cleaning up $(OBJS) files.)
	rm -f *.o  # linux
#	del *.o		# windows

fclean: clean
	$(info Removing $(TARGET) file.)
	rm -f $(TARGET) # linux
#	del $(TARGET).exe	# windows

re: fclean all
