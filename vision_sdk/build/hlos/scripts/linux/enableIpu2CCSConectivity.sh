#!/bin/sh

# In order to connect to the IPU2 the PM_CORE_PWRSTCTRL : LOWPOWERSTATECHANGE
# bit must be cleared.

omapconf write 0x4AE06700 0x3FF0F07
echo on > /sys/bus/platform/devices/55020000.ipu/power/control

