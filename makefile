# target and dir path configure.
TARGET := Practice
WORKDIR := $(shell pwd)
SRCDIR := $(WORKDIR)/src
HDRDIR := $(WORKDIR)/hdr
OBJDIR := $(WORKDIR)/obj

# toolchain configure.
CC ?= gcc
RM ?= rm

# file search.
HEADS := $(shell find $(HDRDIR) -type f -iname "*.h")
SRCS := $(shell find $(SRCDIR) -type f -iname "*.c")
OBJS := $(patsubst $(SRCDIR)%, $(OBJDIR)%, $(patsubst %.c, %.o, $(SRCS)))

# block make flag configure.
IFLAGS += $(addprefix -I, $(HEADS))

TARGET: env
	$(CC) -o $(TARGET) $(OBJS) $(IFLAGS)

%.o: %.c
	$(CC) -g $< -o $@

.PHONY: env
env:
	@echo $(HEADS)
	@echo $(SRCS)
	@echo $(OBJS)

.PHONY: clean
clean: 
	$(RM) $(OBJS)
	$(RM) $(TARGET)