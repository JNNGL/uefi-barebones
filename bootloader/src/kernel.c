#include "kernel.h"

int memcmp(const void* aptr, const void* bptr, uint64_t n) {
    const unsigned char* a = (const unsigned char*)aptr;
    const unsigned char* b = (const unsigned char*)bptr;
    for(uint64_t i = 0; i < n; i++) {
        if(a[i] < b[i]) return -1;
        else if(a[i] > b[i]) return 1;
    }
    return 0;
}

uint8_t load_kernel(EFI_FILE* file, Elf64_Ehdr* dst) {
    Elf64_Ehdr header;
    UINTN info_size;
    EFI_FILE_INFO* info;
    file->GetInfo(file, &gEfiFileInfoGuid, &info_size, NULL);
    ST->BootServices->AllocatePool(EfiLoaderData, info_size, (void**)&info);
    file->GetInfo(file, &gEfiFileInfoGuid, &info_size, (void**)&info);
    UINTN size = sizeof(header);
    file->Read(file, &size, &header);
    if(memcmp(&header.e_ident[EI_MAG0], ELFMAG, SELFMAG) != 0 || header.e_ident[EI_CLASS] != ELFCLASS64
        || header.e_ident[EI_DATA] != ELFDATA2LSB || header.e_type != ET_EXEC || header.e_machine != EM_X86_64
        || header.e_version != EV_CURRENT) {
            return 0;
        }
    Elf64_Phdr* phdrs;
    file->SetPosition(file, header.e_phoff);
    size = header.e_phnum * header.e_phentsize;
    ST->BootServices->AllocatePool(EfiLoaderData, size, (void**)&phdrs);
    file->Read(file, &size, phdrs);
    for(Elf64_Phdr* phdr = phdrs; (char*)phdr < (char*)phdrs + header.e_phnum * header.e_phentsize; 
            phdr = (Elf64_Phdr*)((char*)phdr + header.e_phentsize)) {
        switch(phdr->p_type) {
            case PT_LOAD: {
                int pages = (phdr->p_memsz + 0x1000 - 1) / 0x1000;
                Elf64_Addr segment = phdr->p_paddr;
                ST->BootServices->AllocatePages(AllocateAddress, EfiLoaderData, pages, &segment);
                file->SetPosition(file, phdr->p_offset);
                size = phdr->p_filesz;
                file->Read(file, &size, (void*)segment);
                break;
            }
        }
    }
    *dst = header;
    return 1;
}