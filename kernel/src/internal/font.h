#ifndef KERNEL_INTERNAL_FONT_H
#define KERNEL_INTERNAL_FONT_H

#define PSF1_MAGIC0 0x36
#define PSF1_MAGIC1 0x04

#define PSF1_MODE512    0x01
#define PSF1_MODEHASTAB 0x02
#define PSF1_MODEHASSEQ 0x04
#define PSF1_MAXMODE    0x05

#define PSF1_SEPARATOR 0xFFFF
#define PSF1_STARTSEQ  0xFFFE

struct psf1_header {
    unsigned char magic[2];
    unsigned char mode;
    unsigned char charsize;
};

struct psf1_font {
    struct psf1_header* header;
    void* buf;
};

#endif