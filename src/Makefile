###########################
# Detect OS
###########################
CFLAGS_BASE = -Wall -Wextra -Werror -fopenmp
CFLAGS_BASE_DEBUG = $(CFLAGS_BASE) -g
ifeq ($(OS),Windows_NT)
    SHELL := C:/Program\ Files/Git/bin/bash.exe
    CC = gcc
    FIND = C:/msys64/usr/bin/find.exe
    RM = C:/msys64/usr/bin/rm.exe -f
    DEL_DIR = C:/msys64/usr/bin/rm.exe -rf
    INC_BASE = C:/msys64/mingw64/include
    LIB_BASE = C:/msys64/mingw64/lib
    CFLAGS = $(CFLAGS_BASE_DEBUG) -mconsole
else
    ifeq ($(shell uname),Darwin) # macOs
        CC = gcc-15
        INC_BASE = /opt/homebrew/include
        LIB_BASE = /opt/homebrew/lib
    else
        CC = gcc
        INC_BASE = /usr/local/include
        LIB_BASE = /usr/local/lib
    endif
    CFLAGS = $(CFLAGS_BASE_DEBUG)
    FIND = find
    RM = rm -f
    DEL_DIR = rm -rf
endif

CFLAGS_RELEASE = $(CFLAGS_BASE) -O2 -DRELEASE

################### For memory leak tests macOs #################
#CC = CC
#CFLAGS = -Wall -Wextra -Werror -g -O2 -fsanitize=address
###########################################################

TARGET = pictoascii
LIBSDIR = libs

# Find include directories
INCDIRS := $(shell $(FIND) $(LIBSDIR) -type d 2>/dev/null)
INCFLAGS := $(patsubst %,-I%,$(INCDIRS)) -I$(INC_BASE)

LDFLAGS = -L$(LIB_BASE) -lturbojpeg -lm

SRCS = $(wildcard *.c */*.c)
OBJS = $(SRCS:.c=.o)

###########################
# Targets
###########################

all: $(TARGET)

release: CFLAGS=$(CFLAGS_RELEASE)
release: clean $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

%.o: %.c
	@echo "Compiling: $<"
	$(CC) $(CFLAGS) $(INCFLAGS) -MMD -MP -c "$<" -o "$@"

clean:
	$(RM) $(TARGET) $(OBJS)
	$(RM) $(OBJS:.o=.d)
	$(DEL_DIR) *.dSYM

test:
ifeq ($(OS),Windows_NT)
	@echo "Running tests in Windows..."
	@"$(SHELL)" -c "cd ../tests && ./test.sh"
else
	@echo "Running tests in Unix..."
	@cd ../tests && ./test.sh
endif

.PHONY: all clean test release
