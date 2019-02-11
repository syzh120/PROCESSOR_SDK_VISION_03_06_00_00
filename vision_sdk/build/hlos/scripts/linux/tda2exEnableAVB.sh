#!/bin/sh
# This is to set mux 
# 1) Enable Eth 1 for AVB usecase
i2cset -f -y 4 0x26 0xd0 0xf6
i2cset -f -y 0 0x21 0x67 0xe3
echo "Mux configuration done"