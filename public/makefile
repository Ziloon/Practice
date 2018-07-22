# # toolchain configure.
# CC ?= gcc
# RM ?= rm
# MKDIR ?= mkdir

WORKDIR := $(shell pwd)
SRCDIR := $(WORKDIR)/src
HDRDIR := $(WORKDIR)/hdr
OBJDIR := $(WORKDIR)/obj

SRCS := $(shell find $(SRCDIR) -type f -iname "*.c")
OBJS := $(patsubst $(SRCDIR)%, $(OBJDIR)%, $(SRCS:%.c=%.o))
DEPS := $(OBJS:%.o=%.d)

BLOCK_IFLAGS := $(IFLAGS) -I$(HDRDIR)
BLOCK_CFLAGS := $(CFLAGS) -g -Wall 

all: public_bin

public_bin: $(OBJS)

$(OBJDIR)%.o: $(SRCDIR)%.c $(OBJDIR)%.d
	@echo "-c $(@F)"
	@$(CC) -c $(BLOCK_CFLAGS) $< -o $@ $(BLOCK_IFLAGS)

$(OBJDIR)%.d: $(SRCDIR)%.c
	@$(CC) -MM $(BLOCK_CFLAGS) $< $(BLOCK_IFLAGS) > $@.tmp
	@sed 's,/($*/)/.o[ :]*,/1.o $@ : ,g' < $@.tmp > $@
	@$(RM) $@.tmp

sinclude $(DEPS)

.PHONY: createdir
createdir:
	@if [ ! -e $(OBJDIR) ];then $(MKDIR) $(OBJDIR); fi;

sinclude createdir

.PHONY: env
env:
	@echo [Head files is] $(HDRS)
	@echo [Src  files is] $(SRCS)
	@echo [Objects    is] $(OBJS)
	@echo [Depend     is] $(DEPS)

.PHONY: clean
clean:
	@if [ -e $(OBJDIR) ]; then $(RM) -rf $(OBJDIR); fi;
