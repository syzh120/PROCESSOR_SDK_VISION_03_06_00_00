killall lad_dra7xx
/usr/bin/lad_dra7xx -l lad.txt
insmod /opt/vision_sdk/cmemk.ko phys_start=0xA9000000 phys_end=0xACffffff pools=1x67108863 phys_start_1=0x40400000  phys_end_1=0x40500000

insmod /opt/vision_sdk/debugss_kmodule.ko
insmod /opt/vision_sdk/gdbserverproxy.ko
