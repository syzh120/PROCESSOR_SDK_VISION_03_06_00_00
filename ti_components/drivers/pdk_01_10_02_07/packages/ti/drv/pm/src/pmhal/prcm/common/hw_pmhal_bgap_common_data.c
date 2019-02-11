/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2014
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/**
 * \file hw_pmhal_bgap_common_data.c
 *
 * \brief   Band gap Temperature Sensor data common between tda2xx and tda3xx
 *          is defined in this file. The temperature to ADC conversion is also
 *          defined here.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include "pmhal_bgap.h"
#include "hw_pmhal_bgap_data.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/**< \brief Global LUT which maps the ADC to the temperature mapping. The
 *          two fields here give the minimum and maximum temperatures indicated
 *          by the ADC value. The LUT is indexed using the ADC value read as an
 *          index. The temperature values listed are in milli degree Celsius.
 */
const pmhalBgapRange_t gPmhalBgapAdcMap[PMHAL_BGAP_TOTAL_ADC_SUPPORTED] =
{
    {-40000, -40000},     /* 0x21C, Decimal = 540 */
    {-40000, -40000},     /* 0x21D, Decimal = 541 */
    {-40000, -40000},     /* 0x21E, Decimal = 542 */
    {-40000, -40000},     /* 0x21F, Decimal = 543 */
    {-40000, -39600},     /* 0x220, Decimal = 544 */
    {-39600, -39200},     /* 0x221, Decimal = 545 */
    {-39200, -38800},     /* 0x222, Decimal = 546 */
    {-38800, -38400},     /* 0x223, Decimal = 547 */
    {-38400, -38000},     /* 0x224, Decimal = 548 */
    {-38000, -37600},     /* 0x225, Decimal = 549 */
    {-37600, -37200},     /* 0x226, Decimal = 550 */
    {-37200, -36800},     /* 0x227, Decimal = 551 */
    {-36800, -36400},     /* 0x228, Decimal = 552 */
    {-36400, -36000},     /* 0x229, Decimal = 553 */
    {-36000, -35600},     /* 0x22A, Decimal = 554 */
    {-35600, -35000},     /* 0x22B, Decimal = 555 */
    {-35000, -34400},     /* 0x22C, Decimal = 556 */
    {-34400, -34000},     /* 0x22D, Decimal = 557 */
    {-34000, -33600},     /* 0x22E, Decimal = 558 */
    {-33600, -33200},     /* 0x22F, Decimal = 559 */
    {-33200, -32800},     /* 0x230, Decimal = 560 */
    {-32800, -32400},     /* 0x231, Decimal = 561 */
    {-32400, -32000},     /* 0x232, Decimal = 562 */
    {-32000, -31600},     /* 0x233, Decimal = 563 */
    {-31600, -31200},     /* 0x234, Decimal = 564 */
    {-31200, -30800},     /* 0x235, Decimal = 565 */
    {-30800, -30400},     /* 0x236, Decimal = 566 */
    {-30400, -30000},     /* 0x237, Decimal = 567 */
    {-30000, -29600},     /* 0x238, Decimal = 568 */
    {-29600, -29200},     /* 0x239, Decimal = 569 */
    {-29200, -28800},     /* 0x23A, Decimal = 570 */
    {-28800, -28400},     /* 0x23B, Decimal = 571 */
    {-28400, -28000},     /* 0x23C, Decimal = 572 */
    {-28000, -27400},     /* 0x23D, Decimal = 573 */
    {-27400, -26800},     /* 0x23E, Decimal = 574 */
    {-26800, -26400},     /* 0x23F, Decimal = 575 */
    {-26400, -26000},     /* 0x240, Decimal = 576 */
    {-26000, -25600},     /* 0x241, Decimal = 577 */
    {-25600, -25200},     /* 0x242, Decimal = 578 */
    {-25200, -24800},     /* 0x243, Decimal = 579 */
    {-24800, -24400},     /* 0x244, Decimal = 580 */
    {-24400, -24000},     /* 0x245, Decimal = 581 */
    {-24000, -23600},     /* 0x246, Decimal = 582 */
    {-23600, -23200},     /* 0x247, Decimal = 583 */
    {-23200, -22800},     /* 0x248, Decimal = 584 */
    {-22800, -22400},     /* 0x249, Decimal = 585 */
    {-22400, -22000},     /* 0x24A, Decimal = 586 */
    {-22000, -21600},     /* 0x24B, Decimal = 587 */
    {-21600, -21200},     /* 0x24C, Decimal = 588 */
    {-21200, -20800},     /* 0x24D, Decimal = 589 */
    {-20800, -20200},     /* 0x24E, Decimal = 590 */
    {-20200, -19600},     /* 0x24F, Decimal = 591 */
    {-19600, -19200},     /* 0x250, Decimal = 592 */
    {-19200, -18800},     /* 0x251, Decimal = 593 */
    {-18800, -18400},     /* 0x252, Decimal = 594 */
    {-18400, -18000},     /* 0x253, Decimal = 595 */
    {-18000, -17600},     /* 0x254, Decimal = 596 */
    {-17600, -17200},     /* 0x255, Decimal = 597 */
    {-17200, -16800},     /* 0x256, Decimal = 598 */
    {-16800, -16400},     /* 0x257, Decimal = 599 */
    {-16400, -16000},     /* 0x258, Decimal = 600 */
    {-16000, -15600},     /* 0x259, Decimal = 601 */
    {-15600, -15200},     /* 0x25A, Decimal = 602 */
    {-15200, -14800},     /* 0x25B, Decimal = 603 */
    {-14800, -14400},     /* 0x25C, Decimal = 604 */
    {-14400, -14000},     /* 0x25D, Decimal = 605 */
    {-14000, -13600},     /* 0x25E, Decimal = 606 */
    {-13600, -13200},     /* 0x25F, Decimal = 607 */
    {-13200, -12800},     /* 0x260, Decimal = 608 */
    {-12800, -12200},     /* 0x261, Decimal = 609 */
    {-12200, -11600},     /* 0x262, Decimal = 610 */
    {-11600, -11200},     /* 0x263, Decimal = 611 */
    {-11200, -10800},     /* 0x264, Decimal = 612 */
    {-10800, -10400},     /* 0x265, Decimal = 613 */
    {-10400, -10000},     /* 0x266, Decimal = 614 */
    {-10000, -9600 },     /* 0x267, Decimal = 615 */
    {-9600,  -9200 },     /* 0x268, Decimal = 616 */
    {-9200,  -8800 },     /* 0x269, Decimal = 617 */
    {-8800,  -8400 },     /* 0x26A, Decimal = 618 */
    {-8400,  -8000 },     /* 0x26B, Decimal = 619 */
    {-8000,  -7600 },     /* 0x26C, Decimal = 620 */
    {-7600,  -7200 },     /* 0x26D, Decimal = 621 */
    {-7200,  -6800 },     /* 0x26E, Decimal = 622 */
    {-6800,  -6400 },     /* 0x26F, Decimal = 623 */
    {-6400,  -6000 },     /* 0x270, Decimal = 624 */
    {-6000,  -5600 },     /* 0x271, Decimal = 625 */
    {-5600,  -5200 },     /* 0x272, Decimal = 626 */
    {-5200,  -4800 },     /* 0x273, Decimal = 627 */
    {-4800,  -4200 },     /* 0x274, Decimal = 628 */
    {-4200,  -3600 },     /* 0x275, Decimal = 629 */
    {-3600,  -3200 },     /* 0x276, Decimal = 630 */
    {-3200,  -2800 },     /* 0x277, Decimal = 631 */
    {-2800,  -2400 },     /* 0x278, Decimal = 632 */
    {-2400,  -2000 },     /* 0x279, Decimal = 633 */
    {-2000,  -1600 },     /* 0x27A, Decimal = 634 */
    {-1600,  -1200 },     /* 0x27B, Decimal = 635 */
    {-1200,  -800  },     /* 0x27C, Decimal = 636 */
    {-800,   -400  },     /* 0x27D, Decimal = 637 */
    {-400,   0     },     /* 0x27E, Decimal = 638 */
    {0,      400   },     /* 0x27F, Decimal = 639 */
    {400,    800   },     /* 0x280, Decimal = 640 */
    {800,    1200  },     /* 0x281, Decimal = 641 */
    {1200,   1600  },     /* 0x282, Decimal = 642 */
    {1600,   2000  },     /* 0x283, Decimal = 643 */
    {2000,   2400  },     /* 0x284, Decimal = 644 */
    {2400,   2800  },     /* 0x285, Decimal = 645 */
    {2800,   3200  },     /* 0x286, Decimal = 646 */
    {3200,   3600  },     /* 0x287, Decimal = 647 */
    {3600,   4200  },     /* 0x288, Decimal = 648 */
    {4200,   4800  },     /* 0x289, Decimal = 649 */
    {4800,   5200  },     /* 0x28A, Decimal = 650 */
    {5200,   5600  },     /* 0x28B, Decimal = 651 */
    {5600,   6000  },     /* 0x28C, Decimal = 652 */
    {6000,   6400  },     /* 0x28D, Decimal = 653 */
    {6400,   6800  },     /* 0x28E, Decimal = 654 */
    {6800,   7200  },     /* 0x28F, Decimal = 655 */
    {7200,   7600  },     /* 0x290, Decimal = 656 */
    {7600,   8000  },     /* 0x291, Decimal = 657 */
    {8000,   8400  },     /* 0x292, Decimal = 658 */
    {8400,   8800  },     /* 0x293, Decimal = 659 */
    {8800,   9200  },     /* 0x294, Decimal = 660 */
    {9200,   9600  },     /* 0x295, Decimal = 661 */
    {9600,   10000 },     /* 0x296, Decimal = 662 */
    {10000,  10400 },     /* 0x297, Decimal = 663 */
    {10400,  10800 },     /* 0x298, Decimal = 664 */
    {10800,  11200 },     /* 0x299, Decimal = 665 */
    {11200,  11600 },     /* 0x29A, Decimal = 666 */
    {11600,  12000 },     /* 0x29B, Decimal = 667 */
    {12000,  12400 },     /* 0x29C, Decimal = 668 */
    {12400,  13000 },     /* 0x29D, Decimal = 669 */
    {13000,  13600 },     /* 0x29E, Decimal = 670 */
    {13600,  14000 },     /* 0x29F, Decimal = 671 */
    {14000,  14400 },     /* 0x2A0, Decimal = 672 */
    {14400,  14800 },     /* 0x2A1, Decimal = 673 */
    {14800,  15200 },     /* 0x2A2, Decimal = 674 */
    {15200,  15600 },     /* 0x2A3, Decimal = 675 */
    {15600,  16000 },     /* 0x2A4, Decimal = 676 */
    {16000,  16400 },     /* 0x2A5, Decimal = 677 */
    {16400,  16800 },     /* 0x2A6, Decimal = 678 */
    {16800,  17200 },     /* 0x2A7, Decimal = 679 */
    {17200,  17600 },     /* 0x2A8, Decimal = 680 */
    {17600,  18000 },     /* 0x2A9, Decimal = 681 */
    {18000,  18400 },     /* 0x2AA, Decimal = 682 */
    {18400,  18800 },     /* 0x2AB, Decimal = 683 */
    {18800,  19200 },     /* 0x2AC, Decimal = 684 */
    {19200,  19600 },     /* 0x2AD, Decimal = 685 */
    {19600,  20000 },     /* 0x2AE, Decimal = 686 */
    {20000,  20400 },     /* 0x2AF, Decimal = 687 */
    {20400,  20800 },     /* 0x2B0, Decimal = 688 */
    {20800,  21200 },     /* 0x2B1, Decimal = 689 */
    {21200,  21600 },     /* 0x2B2, Decimal = 690 */
    {21600,  22200 },     /* 0x2B3, Decimal = 691 */
    {22200,  22800 },     /* 0x2B4, Decimal = 692 */
    {22800,  23200 },     /* 0x2B5, Decimal = 693 */
    {23200,  23600 },     /* 0x2B6, Decimal = 694 */
    {23600,  24000 },     /* 0x2B7, Decimal = 695 */
    {24000,  24400 },     /* 0x2B8, Decimal = 696 */
    {24400,  24800 },     /* 0x2B9, Decimal = 697 */
    {24800,  25200 },     /* 0x2BA, Decimal = 698 */
    {25200,  25600 },     /* 0x2BB, Decimal = 699 */
    {25600,  26000 },     /* 0x2BC, Decimal = 700 */
    {26000,  26400 },     /* 0x2BD, Decimal = 701 */
    {26400,  26800 },     /* 0x2BE, Decimal = 702 */
    {26800,  27200 },     /* 0x2BF, Decimal = 703 */
    {27200,  27600 },     /* 0x2C0, Decimal = 704 */
    {27600,  28000 },     /* 0x2C1, Decimal = 705 */
    {28000,  28400 },     /* 0x2C2, Decimal = 706 */
    {28400,  28800 },     /* 0x2C3, Decimal = 707 */
    {28800,  29200 },     /* 0x2C4, Decimal = 708 */
    {29200,  29600 },     /* 0x2C5, Decimal = 709 */
    {29600,  30000 },     /* 0x2C6, Decimal = 710 */
    {30000,  30400 },     /* 0x2C7, Decimal = 711 */
    {30400,  30800 },     /* 0x2C8, Decimal = 712 */
    {30800,  31200 },     /* 0x2C9, Decimal = 713 */
    {31200,  31600 },     /* 0x2CA, Decimal = 714 */
    {31600,  32200 },     /* 0x2CB, Decimal = 715 */
    {32200,  32800 },     /* 0x2CC, Decimal = 716 */
    {32800,  33200 },     /* 0x2CD, Decimal = 717 */
    {33200,  33600 },     /* 0x2CE, Decimal = 718 */
    {33600,  34000 },     /* 0x2CF, Decimal = 719 */
    {34000,  34400 },     /* 0x2D0, Decimal = 720 */
    {34400,  34800 },     /* 0x2D1, Decimal = 721 */
    {34800,  35200 },     /* 0x2D2, Decimal = 722 */
    {35200,  35600 },     /* 0x2D3, Decimal = 723 */
    {35600,  36000 },     /* 0x2D4, Decimal = 724 */
    {36000,  36400 },     /* 0x2D5, Decimal = 725 */
    {36400,  36800 },     /* 0x2D6, Decimal = 726 */
    {36800,  37200 },     /* 0x2D7, Decimal = 727 */
    {37200,  37600 },     /* 0x2D8, Decimal = 728 */
    {37600,  38000 },     /* 0x2D9, Decimal = 729 */
    {38000,  38400 },     /* 0x2DA, Decimal = 730 */
    {38400,  38800 },     /* 0x2DB, Decimal = 731 */
    {38800,  39200 },     /* 0x2DC, Decimal = 732 */
    {39200,  39600 },     /* 0x2DD, Decimal = 733 */
    {39600,  40000 },     /* 0x2DE, Decimal = 734 */
    {40000,  40400 },     /* 0x2DF, Decimal = 735 */
    {40400,  40800 },     /* 0x2E0, Decimal = 736 */
    {40800,  41200 },     /* 0x2E1, Decimal = 737 */
    {41200,  41600 },     /* 0x2E2, Decimal = 738 */
    {41600,  42000 },     /* 0x2E3, Decimal = 739 */
    {42000,  42400 },     /* 0x2E4, Decimal = 740 */
    {42400,  42800 },     /* 0x2E5, Decimal = 741 */
    {42800,  43400 },     /* 0x2E6, Decimal = 742 */
    {43400,  44000 },     /* 0x2E7, Decimal = 743 */
    {44000,  44400 },     /* 0x2E8, Decimal = 744 */
    {44400,  44800 },     /* 0x2E9, Decimal = 745 */
    {44800,  45200 },     /* 0x2EA, Decimal = 746 */
    {45200,  45600 },     /* 0x2EB, Decimal = 747 */
    {45600,  46000 },     /* 0x2EC, Decimal = 748 */
    {46000,  46400 },     /* 0x2ED, Decimal = 749 */
    {46400,  46800 },     /* 0x2EE, Decimal = 750 */
    {46800,  47200 },     /* 0x2EF, Decimal = 751 */
    {47200,  47600 },     /* 0x2F0, Decimal = 752 */
    {47600,  48000 },     /* 0x2F1, Decimal = 753 */
    {48000,  48400 },     /* 0x2F2, Decimal = 754 */
    {48400,  48800 },     /* 0x2F3, Decimal = 755 */
    {48800,  49200 },     /* 0x2F4, Decimal = 756 */
    {49200,  49600 },     /* 0x2F5, Decimal = 757 */
    {49600,  50000 },     /* 0x2F6, Decimal = 758 */
    {50000,  50400 },     /* 0x2F7, Decimal = 759 */
    {50400,  50800 },     /* 0x2F8, Decimal = 760 */
    {50800,  51200 },     /* 0x2F9, Decimal = 761 */
    {51200,  51600 },     /* 0x2FA, Decimal = 762 */
    {51600,  52000 },     /* 0x2FB, Decimal = 763 */
    {52000,  52400 },     /* 0x2FC, Decimal = 764 */
    {52400,  52800 },     /* 0x2FD, Decimal = 765 */
    {52800,  53200 },     /* 0x2FE, Decimal = 766 */
    {53200,  53600 },     /* 0x2FF, Decimal = 767 */
    {53600,  54000 },     /* 0x300, Decimal = 768 */
    {54000,  54400 },     /* 0x301, Decimal = 769 */
    {54400,  54800 },     /* 0x302, Decimal = 770 */
    {54800,  55200 },     /* 0x303, Decimal = 771 */
    {55200,  55600 },     /* 0x304, Decimal = 772 */
    {55600,  56200 },     /* 0x305, Decimal = 773 */
    {56200,  56800 },     /* 0x306, Decimal = 774 */
    {56800,  57200 },     /* 0x307, Decimal = 775 */
    {57200,  57600 },     /* 0x308, Decimal = 776 */
    {57600,  58000 },     /* 0x309, Decimal = 777 */
    {58000,  58400 },     /* 0x30A, Decimal = 778 */
    {58400,  58800 },     /* 0x30B, Decimal = 779 */
    {58800,  59200 },     /* 0x30C, Decimal = 780 */
    {59200,  59600 },     /* 0x30D, Decimal = 781 */
    {59600,  60000 },     /* 0x30E, Decimal = 782 */
    {60000,  60400 },     /* 0x30F, Decimal = 783 */
    {60400,  60800 },     /* 0x310, Decimal = 784 */
    {60800,  61200 },     /* 0x311, Decimal = 785 */
    {61200,  61600 },     /* 0x312, Decimal = 786 */
    {61600,  62000 },     /* 0x313, Decimal = 787 */
    {62000,  62400 },     /* 0x314, Decimal = 788 */
    {62400,  62800 },     /* 0x315, Decimal = 789 */
    {62800,  63200 },     /* 0x316, Decimal = 790 */
    {63200,  63600 },     /* 0x317, Decimal = 791 */
    {63600,  64000 },     /* 0x318, Decimal = 792 */
    {64000,  64400 },     /* 0x319, Decimal = 793 */
    {64400,  64800 },     /* 0x31A, Decimal = 794 */
    {64800,  65200 },     /* 0x31B, Decimal = 795 */
    {65200,  65600 },     /* 0x31C, Decimal = 796 */
    {65600,  66000 },     /* 0x31D, Decimal = 797 */
    {66000,  66400 },     /* 0x31E, Decimal = 798 */
    {66400,  66800 },     /* 0x31F, Decimal = 799 */
    {66800,  67200 },     /* 0x320, Decimal = 800 */
    {67200,  67600 },     /* 0x321, Decimal = 801 */
    {67600,  68000 },     /* 0x322, Decimal = 802 */
    {68000,  68400 },     /* 0x323, Decimal = 803 */
    {68400,  68800 },     /* 0x324, Decimal = 804 */
    {68800,  69200 },     /* 0x325, Decimal = 805 */
    {69200,  69600 },     /* 0x326, Decimal = 806 */
    {69600,  70000 },     /* 0x327, Decimal = 807 */
    {70000,  70400 },     /* 0x328, Decimal = 808 */
    {70400,  70800 },     /* 0x329, Decimal = 809 */
    {70800,  71200 },     /* 0x32A, Decimal = 810 */
    {71200,  71800 },     /* 0x32B, Decimal = 811 */
    {71800,  72400 },     /* 0x32C, Decimal = 812 */
    {72400,  72800 },     /* 0x32D, Decimal = 813 */
    {72800,  73200 },     /* 0x32E, Decimal = 814 */
    {73200,  73600 },     /* 0x32F, Decimal = 815 */
    {73600,  74000 },     /* 0x330, Decimal = 816 */
    {74000,  74400 },     /* 0x331, Decimal = 817 */
    {74400,  74800 },     /* 0x332, Decimal = 818 */
    {74800,  75200 },     /* 0x333, Decimal = 819 */
    {75200,  75600 },     /* 0x334, Decimal = 820 */
    {75600,  76000 },     /* 0x335, Decimal = 821 */
    {76000,  76400 },     /* 0x336, Decimal = 822 */
    {76400,  76800 },     /* 0x337, Decimal = 823 */
    {76800,  77200 },     /* 0x338, Decimal = 824 */
    {77200,  77600 },     /* 0x339, Decimal = 825 */
    {77600,  78000 },     /* 0x33A, Decimal = 826 */
    {78000,  78400 },     /* 0x33B, Decimal = 827 */
    {78400,  78800 },     /* 0x33C, Decimal = 828 */
    {78800,  79200 },     /* 0x33D, Decimal = 829 */
    {79200,  79600 },     /* 0x33E, Decimal = 830 */
    {79600,  80000 },     /* 0x33F, Decimal = 831 */
    {80000,  80400 },     /* 0x340, Decimal = 832 */
    {80400,  80800 },     /* 0x341, Decimal = 833 */
    {80800,  81200 },     /* 0x342, Decimal = 834 */
    {81200,  81600 },     /* 0x343, Decimal = 835 */
    {81600,  82000 },     /* 0x344, Decimal = 836 */
    {82000,  82400 },     /* 0x345, Decimal = 837 */
    {82400,  82800 },     /* 0x346, Decimal = 838 */
    {82800,  83200 },     /* 0x347, Decimal = 839 */
    {83200,  83600 },     /* 0x348, Decimal = 840 */
    {83600,  84000 },     /* 0x349, Decimal = 841 */
    {84000,  84400 },     /* 0x34A, Decimal = 842 */
    {84400,  84800 },     /* 0x34B, Decimal = 843 */
    {84800,  85200 },     /* 0x34C, Decimal = 844 */
    {85200,  85600 },     /* 0x34D, Decimal = 845 */
    {85600,  86000 },     /* 0x34E, Decimal = 846 */
    {86000,  86400 },     /* 0x34F, Decimal = 847 */
    {86400,  86800 },     /* 0x350, Decimal = 848 */
    {86800,  87200 },     /* 0x351, Decimal = 849 */
    {87200,  87600 },     /* 0x352, Decimal = 850 */
    {87600,  88000 },     /* 0x353, Decimal = 851 */
    {88000,  88400 },     /* 0x354, Decimal = 852 */
    {88400,  88800 },     /* 0x355, Decimal = 853 */
    {88800,  89200 },     /* 0x356, Decimal = 854 */
    {89200,  89600 },     /* 0x357, Decimal = 855 */
    {89600,  90000 },     /* 0x358, Decimal = 856 */
    {90000,  90400 },     /* 0x359, Decimal = 857 */
    {90400,  90800 },     /* 0x35A, Decimal = 858 */
    {90800,  91200 },     /* 0x35B, Decimal = 859 */
    {91200,  91600 },     /* 0x35C, Decimal = 860 */
    {91600,  92000 },     /* 0x35D, Decimal = 861 */
    {92000,  92400 },     /* 0x35E, Decimal = 862 */
    {92400,  92800 },     /* 0x35F, Decimal = 863 */
    {92800,  93200 },     /* 0x360, Decimal = 864 */
    {93200,  93600 },     /* 0x361, Decimal = 865 */
    {93600,  94000 },     /* 0x362, Decimal = 866 */
    {94000,  94400 },     /* 0x363, Decimal = 867 */
    {94400,  94800 },     /* 0x364, Decimal = 868 */
    {94800,  95200 },     /* 0x365, Decimal = 869 */
    {95200,  95600 },     /* 0x366, Decimal = 870 */
    {95600,  96000 },     /* 0x367, Decimal = 871 */
    {96000,  96400 },     /* 0x368, Decimal = 872 */
    {96400,  96800 },     /* 0x369, Decimal = 873 */
    {96800,  97200 },     /* 0x36A, Decimal = 874 */
    {97200,  97800 },     /* 0x36B, Decimal = 875 */
    {97800,  98400 },     /* 0x36C, Decimal = 876 */
    {98400,  98800 },     /* 0x36D, Decimal = 877 */
    {98800,  99200 },     /* 0x36E, Decimal = 878 */
    {99200,  99600 },     /* 0x36F, Decimal = 879 */
    {99600,  100000},     /* 0x370, Decimal = 880 */
    {100000, 100400},     /* 0x371, Decimal = 881 */
    {100400, 100800},     /* 0x372, Decimal = 882 */
    {100800, 101200},     /* 0x373, Decimal = 883 */
    {101200, 101600},     /* 0x374, Decimal = 884 */
    {101600, 102000},     /* 0x375, Decimal = 885 */
    {102000, 102400},     /* 0x376, Decimal = 886 */
    {102400, 102800},     /* 0x377, Decimal = 887 */
    {102800, 103200},     /* 0x378, Decimal = 888 */
    {103200, 103600},     /* 0x379, Decimal = 889 */
    {103600, 104000},     /* 0x37A, Decimal = 890 */
    {104000, 104400},     /* 0x37B, Decimal = 891 */
    {104400, 104800},     /* 0x37C, Decimal = 892 */
    {104800, 105200},     /* 0x37D, Decimal = 893 */
    {105200, 105600},     /* 0x37E, Decimal = 894 */
    {105600, 106000},     /* 0x37F, Decimal = 895 */
    {106000, 106400},     /* 0x380, Decimal = 896 */
    {106400, 106800},     /* 0x381, Decimal = 897 */
    {106800, 107200},     /* 0x382, Decimal = 898 */
    {107200, 107600},     /* 0x383, Decimal = 899 */
    {107600, 108000},     /* 0x384, Decimal = 900 */
    {108000, 108400},     /* 0x385, Decimal = 901 */
    {108400, 108800},     /* 0x386, Decimal = 902 */
    {108800, 109200},     /* 0x387, Decimal = 903 */
    {109200, 109600},     /* 0x388, Decimal = 904 */
    {109600, 110000},     /* 0x389, Decimal = 905 */
    {110000, 110400},     /* 0x38A, Decimal = 906 */
    {110400, 110800},     /* 0x38B, Decimal = 907 */
    {110800, 111200},     /* 0x38C, Decimal = 908 */
    {111200, 111600},     /* 0x38D, Decimal = 909 */
    {111600, 112000},     /* 0x38E, Decimal = 910 */
    {112000, 112400},     /* 0x38F, Decimal = 911 */
    {112400, 112800},     /* 0x390, Decimal = 912 */
    {112800, 113200},     /* 0x391, Decimal = 913 */
    {113200, 113600},     /* 0x392, Decimal = 914 */
    {113600, 114000},     /* 0x393, Decimal = 915 */
    {114000, 114400},     /* 0x394, Decimal = 916 */
    {114400, 114800},     /* 0x395, Decimal = 917 */
    {114800, 115200},     /* 0x396, Decimal = 918 */
    {115200, 115600},     /* 0x397, Decimal = 919 */
    {115600, 116000},     /* 0x398, Decimal = 920 */
    {116000, 116400},     /* 0x399, Decimal = 921 */
    {116400, 116800},     /* 0x39A, Decimal = 922 */
    {116800, 117200},     /* 0x39B, Decimal = 923 */
    {117200, 117600},     /* 0x39C, Decimal = 924 */
    {117600, 118000},     /* 0x39D, Decimal = 925 */
    {118000, 118400},     /* 0x39E, Decimal = 926 */
    {118400, 118800},     /* 0x39F, Decimal = 927 */
    {118800, 119200},     /* 0x3A0, Decimal = 928 */
    {119200, 119600},     /* 0x3A1, Decimal = 929 */
    {119600, 120000},     /* 0x3A2, Decimal = 930 */
    {120000, 120400},     /* 0x3A3, Decimal = 931 */
    {120400, 120800},     /* 0x3A4, Decimal = 932 */
    {120800, 121200},     /* 0x3A5, Decimal = 933 */
    {121200, 121600},     /* 0x3A6, Decimal = 934 */
    {121600, 122000},     /* 0x3A7, Decimal = 935 */
    {122000, 122400},     /* 0x3A8, Decimal = 936 */
    {122400, 122800},     /* 0x3A9, Decimal = 937 */
    {122800, 123200},     /* 0x3AA, Decimal = 938 */
    {123200, 123600},     /* 0x3AB, Decimal = 939 */
    {123600, 124000},     /* 0x3AC, Decimal = 940 */
    {124000, 124400},     /* 0x3AD, Decimal = 941 */
    {124400, 124800},     /* 0x3AE, Decimal = 942 */
    {124800, 125000},     /* 0x3AF, Decimal = 943 */
    {125000, 125000}      /* 0x3B1, Decimal = 945 */
};

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

const pmhalBgapRange_t *PmhalBgapGetTemperatureRange(uint32_t adcValue)
{
    const pmhalBgapRange_t *currTempRange;

    if ((adcValue < PMHAL_BGAP_MIN_ADC_VALUE) ||
        (adcValue > PMHAL_BGAP_MAX_ADC_VALUE))
    {
        currTempRange = NULL;
    }
    else
    {
        uint32_t index = adcValue - PMHAL_BGAP_MIN_ADC_VALUE;
        /* Usage of LUT method here is better as the temperature is not
         * approximated here due to the nature of the formulas used in the
         * system to derive temperature from adc value
         */
        currTempRange = &gPmhalBgapAdcMap[index];
    }

    return currTempRange;
}

uint32_t PmhalBgapGetAdcValue(int32_t tempInMilliDegree)
{
    int32_t adcValue;

    /* Formula from the Band gap specification. Calculation using temperature
     * ranges is better in this case as the exact temperature search in the
     * LUT may not match, but a best case ADC value can be derived using the
     * formula.
     *
     * -40 to 0.2C    =(0.42240*(Code-544.177))-39.8
     * 0.6 to 40.2C   =(0.41820*(Code-639.875))+0.6
     * 40.6 to 80.2C  =(0.41196*(Code-735.721))+40.6
     * 80.6 to 125C   =(0.40470*(Code-833.000))+80.6
     */
    if ((tempInMilliDegree >= -40000) && (tempInMilliDegree < 600))
    {
        adcValue =
            (((tempInMilliDegree + 39800) * 100) / 42240) + (544177 / 1000);
    }
    else if ((tempInMilliDegree >= 600) && (tempInMilliDegree < 40600))
    {
        adcValue =
            (((tempInMilliDegree - 600) * 100) / 41820) + (639875 / 1000);
    }
    else if ((tempInMilliDegree >= 40600) && (tempInMilliDegree < 80600))
    {
        adcValue =
            (((tempInMilliDegree - 40600) * 100) / 41196) + (735721 / 1000);
    }
    else if ((tempInMilliDegree >= 80600) && (tempInMilliDegree <= 125000))
    {
        adcValue = (((tempInMilliDegree - 80600) * 100) / 40470) + 833;
    }
    else
    {
        adcValue = 0;
    }

    return (uint32_t) adcValue;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/* None */

