****************************************
TDA3xx GMAC sanity and throughput test
****************************************
1. Unzip the project zip file.
2. Open CCS, go to project explorer, import project
3. Browse to unzipped folder (adaslow_gmac_throughput_ipu)
4. Build project (right click->build)
5. If built without any errors, you should find test binary vayu_throughput_ipu.out in Debug folder
6. Connect EVM to CCS through JTAG. Launch tda2xx Target configuration
7. Connect IPU0_0 core.
8. Load TDA2xx_m4_ammu_config.gel on IPU and run "MMU Config" function under scripts.
8. Load newly created binary onto IPU0_0 and give run.
9. This test transfers 50 packets over Ethernet interface.
10.Below are different configurations enabled in test case file RGMII_CH0_PORT_THPUT.c. Set/unset as per requirement.
    #define ENABLE_PHY_LOOPBACK    0
    #define ENABLE_EXT_LOOPBACK    1
    #define ENABLE_100MBPS_MODE     1
    #define PORT1_ENABLED          1
    #define PORT2_ENABLED           0
11. The console logs are intuitive for debug and test status.