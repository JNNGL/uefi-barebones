set OS=bin/out.img
qemu-system-x86_64 -drive file=%OS% -drive if=pflash,format=raw,unit=0,file=OVMF_CODE.fd,readonly=on -drive if=pflash,format=raw,unit=1,file=OVMF_VARS.fd -net none