#!/bin/bash
make clean
cd bootloader
make bootloader
cd ..
make img