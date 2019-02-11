proc memory_write { fileName startAddr } {

  #Currently setting a constraint that all memory reads and writes would be 

  #64 bit aligned. Last 3 bits of byte address would be 0.

  set bkStAdr [expr ($startAddr - 0x80000000)/8 ]

  set bankStAddr [ format  %x $bkStAdr]

  exec ./DDRsplit $fileName

  memory load Vayu_0_even even_0.bin 0x$bankStAddr 

  memory load Vayu_1_even even_1.bin 0x$bankStAddr 

  memory load Vayu_2_even even_2.bin 0x$bankStAddr 

  memory load Vayu_3_even even_3.bin 0x$bankStAddr 

  memory load Vayu_0_odd odd_0.bin 0x$bankStAddr 

  memory load Vayu_1_odd odd_1.bin 0x$bankStAddr 

  memory load Vayu_2_odd odd_2.bin 0x$bankStAddr 

  memory load Vayu_3_odd odd_3.bin 0x$bankStAddr 

}

