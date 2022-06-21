CC = x86_64-linux-gnu-gcc
LD = x86_64-linux-gnu-ld
CFLAGS = -ffreestanding -fshort-wchar
LINKERSCRIPT = kernel.ld
LDFLAGS = -T $(LINKERSCRIPT) -Bsymbolic -nostdlib -static

SRC_DIR = src
OBJ_DIR = lib
BIN_DIR = bin

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

SRC = $(call rwildcard,$(SRC_DIR),*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo CC $^
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $^ -o $@

link: $(OBJS)
	@echo LD kernel.elf
	@mkdir -p $(BIN_DIR)
	@$(LD) $(LDFLAGS) $(OBJS) -o $(BIN_DIR)/kernel.elf

kernel: link