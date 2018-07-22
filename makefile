# toolchain configure.
CC ?= gcc
RM ?= rm
MKDIR ?= mkdir

WORKDIR := $(shell pwd)
OUTPUT := $(WORKDIR)/output
SERVER_DIR := $(WORKDIR)/server
SHELL_DIR := $(WORKDIR)/shell
SERVER_BIN := server.out
SHELL_BIN := shell.out

all: server shell

server: $(OUTPUT)/$(SERVER_BIN)

shell: $(OUTPUT)/$(SHELL_BIN)

$(OUTPUT)/$(SERVER_BIN):
	@make -C $(SERVER_DIR)
	@cp $(SERVER_DIR)/obj/$(SERVER_BIN) $(OUTPUT)/

$(OUTPUT)/$(SHELL_BIN):
	@make -C $(SHELL_DIR)
	@cp $(SHELL_DIR)/obj/$(SHELL_BIN) $(OUTPUT)/

createdir:
	@if [ ! -e $(OUTPUT) ];then $(MKDIR) $(OUTPUT); fi;

sinclude createdir
	
clean: server_clean shell_clean
	@if [ -e $(OUTPUT) ]; then $(RM) -rf $(OUTPUT); fi;

server_clean:
	@make -C $(SERVER_DIR) clean

shell_clean:
	@make -C $(SHELL_DIR) clean