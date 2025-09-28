CC = gcc-15
CFLAGS = -Wall -Wextra -Werror -fopenmp -g
СFLAGS_RELEASE = -Wall -Wextra -Werror -fopenmp -O2 -DRELEASE

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

release: CFLAGS=$(CFLAGS_RELEASE)
release: clean $(TARGET)

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

.PHONY: all clean test release
