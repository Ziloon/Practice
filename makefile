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
#$(addprefix -I, $(HDRS))

sinclude $(DEPS)
sinclude createdir

TARGET: env $(OBJS) createdir
	@echo "-c $@"
	@$(CC) -o $(TARGET) $(OBJS) $(IFLAGS)

$(OBJDIR)%.o: $(SRCDIR)%.c $(OBJDIR)%.o
	@echo "-c $@"
	@$(CC) -c $(CFLAGS) $< -o $@ $(IFLAGS)

$(OBJDIR)%.d: $(SRCDIR)%.c
	@echo "-c $@"
	@$(CC) -MM $(CFLAGS) $< $(IFLAGS) > $@.tmp
	@sed 's,/($*/)/.o[ :]*,/1.o $@ : ,g' < $@.tmp > $@
	@$(RM) $@.tmp

.PHONY: createdir
createdir:
	@if [ ! -e $(OBJDIR) ];then $(MKDIR) $(OBJDIR); echo "-c $(OBJDIR)"; fi;

.PHONY: env
env:
	@echo [Head files is] $(HDRS)
	@echo [Src  files is] $(SRCS)
	@echo [Objects    is] $(OBJS)
	@echo [Depend     is] $(DEPS)

.PHONY: clean
clean:
	@if [ -e $(OBJDIR) ]; then $(RM) -rf $(OBJDIR); echo "-d $(OBJDIR)"; fi;
	@if [ -e $(TARGET) ]; then $(RM) -rf $(TARGET); echo "-d $(TARGET)"; fi;


