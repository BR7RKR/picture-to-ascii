CC = gcc-15
CFLAGS = -Wall -Wextra -Werror -fopenmp -g -O2 #-DRELEASE flag for release

################### For memory leak tests #################
#CC = CC
#CFLAGS = -Wall -Wextra -Werror -g -O2 -fsanitize=address
###########################################################

TARGET = pictoascii
LIBSDIR = libs

INCDIRS := $(shell find $(LIBSDIR) -type d)
INCFLAGS := $(patsubst %,-I%,$(INCDIRS)) -I/opt/homebrew/include

LDFLAGS = -L/opt/homebrew/lib -lturbojpeg

SRCS = $(shell find . -name '*.c')
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

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
