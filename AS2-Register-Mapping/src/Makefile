
#############################################################
# 
# Description: Makefile, for 'ATmega32' target uController.
# Author: Eng. Hazem Anwer
# Github: https://github.com/hazemanwer2000
# 
#############################################################



# Make workspace (usually '.make')
MAKE_WS := .make

# INCLUDE: Python library
include $(MAKE_WS)/py.mk


# Whitespace-separated list of '.obj' (library) files
LIB_OBJS := $(call GET_FILES,.,.obj)

# Whitespace-separated list of source files
SRCS := $(call GET_FILES,.,.cpp)

# Whitespace-separated list of directories, containing header files, prefixed with '-I'
HDR_DIRS := $(addprefix -I,$(call GET_DIRS,.,.h))

# Mapping of 'SRCS' to assembly, object, dependency files
ASMS := $(SRCS:.cpp=.s)
OBJS := $(SRCS:.cpp=.o)
DEPS := $(SRCS:.cpp=.d)



# Compiler Optimization Options
OPTIMIZE := -O0

# Compiler Option, related to target
SPECS := #



# Compiler command (or, path)
CC := g++

# Object-copy (or, translator, e.g: '.elf' binary to '.hex' ASCII) command (or, path)
OBJCPY := #



# Compiler, pre-processor, linker, and object-copy flags
CFLAGS := -std=c++11 $(SPECS) $(OPTIMIZE)
PPFLAGS := $(HDR_DIRS)
LDFLAGS := #
CPY_FLAGS := #



# Name of target executable file
TARGET := main.exe

.PHONY: clean all

all: $(TARGET)

$(TARGET): $(OBJS) $(LIB_OBJS)
	$(CC) $(PPFLAGS) $(CFLAGS) $(LDFLAGS) $^ -o $@
#	$(OBJCPY) $(CPY_FLAGS) $@ $(@:.elf=.hex)

clean:
	$(PY_DEL) $(TARGET) $(DEPS) $(OBJS) $(ASMS)

# Note: '*.s' file won't be updated if included headers change
%.s: %.cpp
	$(CC) -S $(PPFLAGS) $(CFLAGS) $^ -o $@

%.d: %.cpp
	$(CC) $(PPFLAGS) -MM -MT $(@:.d=.o) $^ > $@
	$(PY_APPEND_CMD) $@ $(CC) -c $(PPFLAGS) $(CFLAGS) $^ -o $(@:.d=.o)



# Including dependencies (case: No command)
ifeq (,$(MAKECMDGOALS))
-include $(DEPS)
endif

# Including dependencies (case: 'all')
ifeq (all,$(MAKECMDGOALS))
-include $(DEPS)
endif