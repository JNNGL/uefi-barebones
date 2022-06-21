@echo -off
mode 80 25

cls
if exist .\EFI\BOOT\BOOTX64.EFI then
 .\EFI\BOOT\BOOTX64.EFI
 goto END
endif

if exist fs0:\EFI\BOOT\BOOTX64.EFI then
 fs0:
 EFI\BOOT\BOOTX64.EFI
 goto END
endif

if exist fs1:\EFI\BOOT\BOOTX64.EFI then
 fs1:
 EFI\BOOT\BOOTX64.EFI
 goto END
endif

if exist fs2:\EFI\BOOT\BOOTX64.EFI then
 fs2:
 EFI\BOOT\BOOTX64.EFI
 goto END
endif

if exist fs3:\EFI\BOOT\BOOTX64.EFI then
 fs3:
 EFI\BOOT\BOOTX64.EFI
 goto END
endif

if exist fs4:\EFI\BOOT\BOOTX64.EFI then
 fs4:
 EFI\BOOT\BOOTX64.EFI
 goto END
endif

if exist fs5:\EFI\BOOT\BOOTX64.EFI then
 fs5:
 EFI\BOOT\BOOTX64.EFI
 goto END
endif

if exist fs6:\EFI\BOOT\BOOTX64.EFI then
 fs6:
 EFI\BOOT\BOOTX64.EFI
 goto END
endif

if exist fs7:\EFI\BOOT\BOOTX64.EFI then
 fs7:
 EFI\BOOT\BOOTX64.EFI
 goto END
endif

 echo "Unable to find bootloader".
 
:END
