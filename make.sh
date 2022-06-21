#!/bin/bash
make clean
cd bootloader
make bootloader
cd ../kernel
make kernel
cd ..
make img