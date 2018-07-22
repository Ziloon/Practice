# toolchain configure.
CC ?= gcc
RM ?= rm
MKDIR ?= mkdir

# target and dir path configure.
WORKDIR := $(shell pwd)

PUBLIC_DIR := $(WORKDIR)/../public
PUBLIC_HDR_DIR := $(PUBLIC_DIR)/hdr
PUBLIC_SRC_DIR := $(PUBLIC_DIR)/src
PUBLIC_OBJ_DIR := $(PUBLIC_DIR)/obj
PUBLIC_SRCS := $(shell find $(PUBLIC_SRC_DIR) -type f -iname "*.c")
PUBLIC_OBJS := $(patsubst $(PUBLIC_SRC_DIR)%, $(PUBLIC_OBJ_DIR)%, $(PUBLIC_SRCS:%.c=%.o))

SRCDIR := $(WORKDIR)/src
HDRDIR := $(WORKDIR)/hdr $(PUBLIC_HDR_DIR)
OBJDIR := $(WORKDIR)/obj
TARGET := $(OBJDIR)/server.out
SRCS := $(shell find $(SRCDIR) -type f -iname "*.c")
OBJS := $(patsubst $(SRCDIR)%, $(OBJDIR)%, $(SRCS:%.c=%.o))
DEPS := $(OBJS:%.o=%.d)

# block make flag configure.
IFLAGS += $(addprefix -I, $(HDRDIR))
CFLAGS += -g -Wall 
LFLAGS += 

export CC RM MKDIR IFLAGS CFLAGS

all: $(TARGET)

$(TARGET): $(OBJS) public_bin
	@echo "-c $(@F)"
	@$(CC) -o $@ $(OBJS) $(PUBLIC_OBJS) $(CFLAGS) $(LFLAGS)

$(OBJDIR)%.o: $(SRCDIR)%.c $(OBJDIR)%.d
	@echo "-c $(@F)"
	@$(CC) -c $(CFLAGS) $< -o $@ $(IFLAGS)

$(OBJDIR)%.d: $(SRCDIR)%.c
	@$(CC) -MM $(CFLAGS) $< $(IFLAGS) > $@.tmp
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
clean: public_bin_clean
	@if [ -e $(OBJDIR) ]; then $(RM) -rf $(OBJDIR); fi;
	@if [ -e $(TARGET) ]; then $(RM) -rf $(TARGET); echo "-d $(TARGET)"; fi;


.PHONY: public_bin public_bin_clean
public_bin:
	@make -s -C $(PUBLIC_DIR)

public_bin_clean:
	@make -C $(PUBLIC_DIR) clean

