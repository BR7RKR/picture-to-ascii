CC = CC
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
TARGET = pictoascii
LIBSDIR = libs

INCDIRS := $(shell find $(LIBSDIR) -type d)
INCFLAGS := $(patsubst %,-I%,$(INCDIRS))

SRCS = $(shell find . -name '*.c')
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCFLAGS) -o $@ $^

%.o: %.c
	@echo "Compiling the app: $<"
	$(CC) $(CFLAGS) $(INCFLAGS) -MMD -MP -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)
	rm -f $(OBJS:.o=.d)
	rm -rf *.dSYM
	
test:
	cd ../tests && ./test.sh

.PHONY: all clean test
