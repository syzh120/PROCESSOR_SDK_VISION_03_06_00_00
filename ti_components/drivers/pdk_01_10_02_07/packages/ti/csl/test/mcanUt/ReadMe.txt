--------------------------------------------------------------------------------
::BOARD TO BOARD SETUP::
--------------------------------------------------------------------------------
MCAN is supported only on TDA3xx SR2.0, Board Rev.D and above and TDA2Px.
1. TDA3xx Setup:
           J6120 Connector/CANBUS2
     _______                     _______
    |       | 1<----CANH----->1 |       |
    |  EVM  | 2<----GND------>2 |  EVM  |
    |   1   | 3<----CANL----->3 |   2   |
    |_______|                   |_______|

The app needs to be run in 4 different execution for regression of all tests.
2. TDA2Ps Setup:
           J20 Connector/DCAN1
     _______                     _______
    |       | 4<----CANH----->4 |       |
    |  EVM  | 5<----GND------>5 |  EVM  |
    |   1   | 3<----CANL----->3 |   2   |
    |_______|                   |_______|

3. For all tests Rx side application should be run first, wherever applicable.

--------------------------------------------------------------------------------
MCAN UT main menu:
1: Manual testing (select specific test case to run)
2. Sanity testing.
3: Regression testing.
4: Full testing.
5: Performance testing.
6: DMA Tx Application.
7: DMA Rx Application.
r: Receiver Side Application.
p: Performance Receiver Side Application.
d: Display test cases.
t: Display test case Details.
g: Generate test report.
s: System Settings.
q: Quit.
--------------------------------------------------------------------------------


::OPTIONS TO SELECT TO RUN SPECIFIC TEST CASE::
--------------------------------------------------------------------------------
ID| Description                                   |Tx Side|Rx Side|Internal LB |
  |                                               |Options|Options|Available   |
--- ----------------------------------------------|---------------|-------------
(Run 1)
1 | MCAN: CAN FD Mode with Bit Rate Switching ON  |1/1    |r      |Y           |
2 | MCAN: Classic CAN Mode                        |1/2    |r      |Y           |
3 | MCAN: CAN FD Mode with Bit Rate Switching OFF |1/3    |r      |Y           |
4 | MCAN: External Time-Stamp                     |1/4    |r      |Y           |
5 | MCAN: High Priority Messages                  |1/5    |r      |Y           |
6 | MCAN: Internal Loopback                       |1/6    |r      |Y           |
7 | MCAN: Tx Mixed Config. With Buffer and FIFO   |1/7    |r      |Y           |
8 | MCAN: Tx Mixed Config. With Buffer and Queue  |1/8    |r      |Y           |
10| MCAN: ECC Test                                |1/10   |r      |Y           |
14| MCAN: Programmable Bit rate                   |1/14   |r      |Y           |
(Run 2)
9 | MCAN: Throughput                              |5      |p      |N           |
(Run 3)
13| MCAN: DMA Events                              |6      |7      |N           |
(Run 4)
11| MCAN: ECC Self Test => SEC Test               |1/11   |NR     |Y           |
12| MCAN: ECC Self Test => DED Test               |1/12   |NR     |Y           |
16| MCAN: External Time-Stamp Overflow Interrupt  |1/16   |NR     |Y           |
17| MCAN: Pin State                               |1/17   |NR     |Y           |
18| MCAN: Clock Stop Request                      |1/18   |NR     |Y           |
19| MCAN: Time Stamp Counter Reset                |1/19   |NR     |Y           |
(Run 5)
15| MCAN: Node State Transitions*                 |1/15   |NR     |Y           |
(Run 6)
20| MCAN: Bus Monitoring Mode**                   |1/20   |Tx(1/1)|N           |
--------------------------------------------------------------------------------
NR: Not required to run Rx Side application.
Tx: Other node should be transmitter and will get ACK error on message
    transmission. This is manual/visual check.
All tests for which Rx side option is either 'r' or 'NA' can be run back to
back in single run.

* - For Bus Off test(MCAN: Node State Transitions), short CANH and CANL.
    For this test, two boards are not needed.

** - Transmitter node shall get Ack Error.
     You can use PCAN for Tx, which will show Ack Error.
     You can also use the another EVM acting as Tx (option 1/1), Transmission will fail with Ack Error.
