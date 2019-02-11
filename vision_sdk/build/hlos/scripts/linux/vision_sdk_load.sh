./memcache_load.sh
# Script to mask display inrerrupt on A15 as the DSS partition is not clean between M4 and A15
./disableDssInterruptsOnA15.sh
./enableIpu2CCSConectivity.sh

# Enable stat collector utility
omapconf write 0x4a008e20 0x1
omapconf write 0x4a008e28 0x1

# set variable to specify test data for OpenVX conformance, tutorials 
# When OpenVX is not present, there are no side effects
export VX_TEST_DATA_PATH=/opt/openvx/test_data
