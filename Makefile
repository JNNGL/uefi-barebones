SHELL := /bin/bash
BIN_DIR = bin
OBJ_DIR = lib
BOOTLOADER_DIR = bootloader
KERNEL_DIR = kernel
NAME = out

clean:
	rm -rf $(BIN_DIR)
	rm -rf $(BOOTLOADER_DIR)/$(BIN_DIR)
	rm -rf $(BOOTLOADER_DIR)/$(OBJ_DIR)
	rm -rf $(KERNEL_DIR)/$(BIN_DIR)
	rm -rf $(KERNEL_DIR)/$(OBJ_DIR)

img:
	@mkdir -p $(BIN_DIR)
	dd if=/dev/zero of=$(BIN_DIR)/$(NAME).img bs=512 count=93750
	mformat -i $(BIN_DIR)/$(NAME).img -f 1440 ::
	mmd -i $(BIN_DIR)/$(NAME).img ::/EFI
	mmd -i $(BIN_DIR)/$(NAME).img ::/EFI/BOOT
	mcopy -i $(BIN_DIR)/$(NAME).img $(BOOTLOADER_DIR)/$(BIN_DIR)/BOOTX64.EFI ::/EFI/BOOT
	mcopy -i $(BIN_DIR)/$(NAME).img startup.nsh ::
	mcopy -i $(BIN_DIR)/$(NAME).img $(KERNEL_DIR)/$(BIN_DIR)/kernel.elf ::

iso: img
	xorriso -as mkisofs -R -f -e $(NAME).img -no-emul-boot -o $(BIN_DIR)/$(NAME).iso $(BIN_DIR)
