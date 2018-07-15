TARGET := Practice

HEADS := $(shell find . -type f -iname "*.h")
SRCS := $(shell find . -type f -iname "*.c")
OBJS := $(patsubst %.c, %.o, $(SRCS))

CC ?= gcc
RM ?= rm


IFLAGS += $(addprefix -I, $(HEADS))

TARGET:
	@echo $(HEADS)
	@echo $(SRCS)
	@echo $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(IFLAGS)


.PHONY: clean

clean: 
	$(RM) $(OBJS)
	$(RM) $(TARGET)