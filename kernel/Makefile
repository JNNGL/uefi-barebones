CC = x86_64-linux-gnu-gcc
ASM = nasm
LD = x86_64-linux-gnu-ld
CFLAGS = -ffreestanding -fshort-wchar
ASMFLAGS = 
LINKERSCRIPT = kernel.ld
LDFLAGS = -T $(LINKERSCRIPT) -Bsymbolic -nostdlib -static

SRC_DIR = src
OBJ_DIR = lib
BIN_DIR = bin

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

SRC = $(call rwildcard,$(SRC_DIR),*.c)
ASM_SRC = $(call rwildcard,$(SRC_DIR),*.s)

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC)) 
OBJS += $(patsubst $(SRC_DIR)/%.s, $(OBJ_DIR)/%_.o, $(ASM_SRC))

INTERRUPTS = internal/interrupts

$(OBJ_DIR)/$(INTERRUPTS).o: $(SRC_DIR)/$(INTERRUPTS).c
	@echo CC $^
	@mkdir -p $(@D)
	@$(CC) -mno-red-zone -mgeneral-regs-only -ffreestanding -c $^ -o $@

$(OBJ_DIR)/%_.o: $(SRC_DIR)/%.s
	@echo ASM $^
	@mkdir -p $(@D)
	@$(ASM) $(ASMFLAGS) $^ -f elf64 -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo CC $^
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $^ -o $@

link: $(OBJS)
	@echo LD kernel.elf
	@mkdir -p $(BIN_DIR)
	@$(LD) $(LDFLAGS) $(OBJS) -o $(BIN_DIR)/kernel.elf

kernel: link