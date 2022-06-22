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
	dd if=/dev/zero of=$(BIN_DIR)/$(NAME).img bs=1k count=1440
	mformat -i $(BIN_DIR)/$(NAME).img -f 1440 ::
	mmd -i $(BIN_DIR)/$(NAME).img ::/EFI
	mmd -i $(BIN_DIR)/$(NAME).img ::/EFI/BOOT
	mcopy -i $(BIN_DIR)/$(NAME).img $(BOOTLOADER_DIR)/$(BIN_DIR)/BOOTX64.EFI ::/EFI/BOOT
	mcopy -i $(BIN_DIR)/$(NAME).img startup.nsh ::
	mcopy -i $(BIN_DIR)/$(NAME).img $(KERNEL_DIR)/$(BIN_DIR)/kernel.elf ::
	mcopy -i $(BIN_DIR)/$(NAME).img zap-ext-vga16.psf ::

iso: img
	@rm -f $(BIN_DIR)/$(NAME).iso
	@mkdir -pv iso/EFI/BOOT
	@cp -v $(BOOTLOADER_DIR)/$(BIN_DIR)/BOOTX64.EFI iso/EFI/BOOT
	@cp -v startup.nsh iso
	@cp -v $(KERNEL_DIR)/$(BIN_DIR)/kernel.elf iso
	@cp -v $(BIN_DIR)/$(NAME).img iso/fat.img
	@cp -v zap-ext-vga16.psf iso
	xorriso -as mkisofs -R -f -eltorito-alt-boot -e EFI/BOOT/BOOTX64.EFI -no-emul-boot -o $(BIN_DIR)/$(NAME).iso iso
	@rm -rf iso
