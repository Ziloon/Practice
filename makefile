# target and dir path configure.
TARGET := Practice
WORKDIR := $(shell pwd)
SRCDIR := $(WORKDIR)/src
HDRDIR := $(WORKDIR)/hdr
OBJDIR := $(WORKDIR)/obj

# toolchain configure.
CC ?= gcc
RM ?= rm
MKDIR = mkdir

# file search.
HDRS := $(shell find $(HDRDIR) -type f -iname "*.h")
SRCS := $(shell find $(SRCDIR) -type f -iname "*.c")
OBJS := $(patsubst $(SRCDIR)%, $(OBJDIR)%, $(SRCS:%.c=%.o))
DEPS := $(OBJS:%.o=%.d)

# block make flag configure.
IFLAGS += -I$(HDRDIR)
CFLAGS += -g
#$(addprefix -I, $(HDRS))

all: $(TARGET)

$(TARGET): $(OBJS)
	@echo "-c $(@F)"
	@$(CC) -o $@ $(OBJS) $(CFLAGS) $(IFLAGS) $(LFLAGS)

$(OBJDIR)%.o: $(SRCDIR)%.c $(OBJDIR)%.d
	@echo "-c $(@F)"
	@$(CC) -c $(CFLAGS) $< -o $@ $(IFLAGS)

$(OBJDIR)%.d: $(SRCDIR)%.c
	@echo "-c $(@F)"
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
clean:
	@if [ -e $(OBJDIR) ]; then $(RM) -rf $(OBJDIR); fi;
	@if [ -e $(TARGET) ]; then $(RM) -rf $(TARGET); echo "-d $(TARGET)"; fi;


