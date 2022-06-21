SHELL := /bin/bash
BIN_DIR = bin
BOOTLOADER_DIR = bootloader
NAME = out

clean:
	rm -rf $(BIN_DIR)
	rm -rf $(BOOTLOADER_DIR)/bin
	rm -rf $(BOOTLOADER_DIR)/lib

img:
	@mkdir -p $(BIN_DIR)
	dd if=/dev/zero of=$(BIN_DIR)/$(NAME).img bs=1k count=1440
	mformat -i $(BIN_DIR)/$(NAME).img -f 1440 ::
	mmd -i $(BIN_DIR)/$(NAME).img ::/EFI
	mmd -i $(BIN_DIR)/$(NAME).img ::/EFI/BOOT
	mcopy -i $(BIN_DIR)/$(NAME).img $(BOOTLOADER_DIR)/$(BIN_DIR)/BOOTX64.EFI ::/EFI/BOOT
	mcopy -i $(BIN_DIR)/$(NAME).img startup.nsh ::

iso: img
	xorriso -as mkisofs -R -f -e $(NAME).img -no-emul-boot -o $(BIN_DIR)/$(NAME).iso $(BIN_DIR)
