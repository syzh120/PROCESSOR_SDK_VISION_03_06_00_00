#!/bin/bash
export var=$3
export profile=$2
export soc=$1

# Available options debug/release
if [ -z $profile ]
then
    export profile=debug
fi

if [ -z $var ]
then
    export var=evm
fi

if [ "$soc" == "tda2px" ]; then
	export core="a15_0"
	export ext="xa15fg"
elif [ "$soc" == "tda3xx" ]; then
	export core="ipu1_0"
	export ext="xem4"
elif [ "$soc" == "tda2ex" ]; then
	export core="a15_0"
	export ext="xa15fg"
elif [ "$soc" == "tda2xx" ]; then
	export core="a15_0"
	export ext="xa15fg"
else
	echo "Invalid configuration"
        echo "Usage:"
        echo "sbl_flash_create <soc> <profile>"
        exit 0
fi

export board="$soc"-"$var"
export EXTERNAL_SW_ROOT=/datalocal/ti_components/cg_tools/linux
export PDK_ROOTDIR=$PWD/../../../..

export Gcc_Tools_Path=$EXTERNAL_SW_ROOT/gcc-arm-none-eabi-4_9-2015q3/bin

export Sbl_Elf_Path=$PDK_ROOTDIR/binary/sbl/mflash_uart/"$board"

rm ./sbl_mflash_"$board"

"$Gcc_Tools_Path/arm-none-eabi-objcopy" --gap-fill=0xff -O binary $Sbl_Elf_Path/sbl_mflash_uart_"$core"_"$profile".$ext ./sbl_mflash_"$board"
