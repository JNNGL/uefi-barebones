CC = x86_64-linux-gnu-gcc
LD = x86_64-linux-gnu-ld
OBJCOPY = objcopy
GNU_EFI = ../gnu-efi
CFLAGS = -ffreestanding -fshort-wchar -I$(GNU_EFI)/inc -I$(GNU_EFI)/inc/x86_64 -I$(GNU_EFI)/inc/protocol -mno-red-zone -mno-avx -fpic -g -O2 -Wall -Wextra -Werror -fno-strict-aliasing -fno-stack-protector -fno-stack-check -fno-merge-all-constants -DCONFIG_x86_64 -DGNU_EFI_USE_MS_ABI -maccumulate-outgoing-args --std=c11 -D__KERNEL__ -I/usr/src/sys/build/include
LDFLAGS = -L$(GNU_EFI)/x86_64/lib -L$(GNU_EFI)/x86_64/gnuefi -T $(GNU_EFI)/gnuefi/elf_x86_64_efi.lds -Bsymbolic -nostdlib -shared --warn-common --no-undefined --fatal-warnings --build-id=sha1 $(GNU_EFI)/x86_64/gnuefi/crt0-efi-x86_64.o
OBJCOPYFLAGS = -j .text -j .sdata -j .data -j .dynamic -j .dynsym  -j .rel -j .rela -j .rel.* -j .rela.* -j .rel* -j .rela* -j .reloc --target efi-app-x86_64 --subsystem=10

BIN_DIR = bin
SRC_DIR = src
OBJ_DIR = lib

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

SRC = $(call rwildcard,$(SRC_DIR),*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC)) $(OBJ_DIR)/data.o

$(OBJ_DIR)/data.o: $(GNU_EFI)/lib/data.c
	@echo CC $^
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo CC $^
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $^ -o $@

bootloader: $(OBJS)
	@echo LD bootloader.so
	@mkdir -p $(BIN_DIR)
	@$(LD) $(LDFLAGS) $(OBJS) -o $(BIN_DIR)/bootloader.so -lgnuefi -lefi
	@echo OBJCOPY BOOTX64.EFI
	@$(OBJCOPY) $(OBJCOPYFLAGS) $(BIN_DIR)/bootloader.so $(BIN_DIR)/BOOTX64.EFI

clean:
	rm -rf bin
	rm -rf lib