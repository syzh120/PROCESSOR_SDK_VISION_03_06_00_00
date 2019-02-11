
memcache_unload.sh 2>/dev/null

insmod ./bin/memcache.ko
# Create 4 pools each of size 1280 * 720 * 1.5 * 8  = 8294400 bytes
# Start and end addresses have to be same as carveout in the device tree
# HACK: Avoid DSP MMU crash due to access overflow
#       end = 0xA8000000 + (1280 * 720 * 1.5 * 8 * 4)
#       Rest address space from end to 0xAA000000 is still mapped to DSP
#       Because we start allocating from end onwards, DSP access overflow
#       won't result in a MMU fault.
insmod ./bin/cmemk.ko phys_start=0xa9000000 phys_end=0xaafa4000 pools=4x8294400

if [ ! -f /dev/memcache ]
then
    major=$(awk '$2=="/dev/memcache" {print $1}' /proc/devices)
    mknod /dev/memcache c ${major} 0
fi

