###########################
# Detect OS
###########################
ifeq ($(OS),Windows_NT)
    SHELL := C:/Program\ Files/Git/bin/bash.exe
    CC = C:/msys64/mingw64/bin/gcc.exe
    FIND = C:/msys64/usr/bin/find.exe
    RM = C:/msys64/usr/bin/rm.exe -f
    DEL_DIR = C:/msys64/usr/bin/rm.exe -rf
    INC_BASE = C:/msys64/mingw64/include
    LIB_BASE = C:/msys64/mingw64/lib
    CFLAGS = -Wall -Wextra -Werror -fopenmp -g -mconsole
else
    CC = gcc-15
    FIND = find
    RM = rm -f
    DEL_DIR = rm -rf
    INC_BASE = /opt/homebrew/include
    LIB_BASE = /opt/homebrew/lib
    CFLAGS = -Wall -Wextra -Werror -fopenmp -g
endif

CFLAGS_RELEASE = -Wall -Wextra -Werror -fopenmp -O2 -DRELEASE

################### For memory leak tests #################
#CC = CC
#CFLAGS = -Wall -Wextra -Werror -g -O2 -fsanitize=address
###########################################################

TARGET = pictoascii
LIBSDIR = libs

# Find include directories
INCDIRS := $(shell $(FIND) $(LIBSDIR) -type d 2>/dev/null)
INCFLAGS := $(patsubst %,-I%,$(INCDIRS)) -I$(INC_BASE)

LDFLAGS = -L$(LIB_BASE) -lturbojpeg

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
