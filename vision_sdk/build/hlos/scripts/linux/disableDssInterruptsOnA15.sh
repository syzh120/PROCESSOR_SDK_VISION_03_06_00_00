#!/bin/sh
#disable display interruts from a15
# this is a temporary patch

# Identified that 20 is irq number for DISPC_IRQ on A15. 
# grep for crossbar req and disable it
# update ipks in case of j6-eco

crossbar=`omapconf dump crossbar irq mpu  | grep DISPC | awk -F" " '{ print $4}'`
# modify the last 4 bits
`omapconf clear bit $crossbar 0`
`omapconf clear bit $crossbar 1`
`omapconf clear bit $crossbar 2`
`omapconf clear bit $crossbar 3`
`omapconf clear bit $crossbar 4`
`omapconf clear bit $crossbar 5`
`omapconf clear bit $crossbar 6`
`omapconf clear bit $crossbar 7`
`omapconf clear bit $crossbar 8`
val=`omapconf read $crossbar 2>&1 | grep -v omapconf`
echo "updated $crossbar value is $val"
