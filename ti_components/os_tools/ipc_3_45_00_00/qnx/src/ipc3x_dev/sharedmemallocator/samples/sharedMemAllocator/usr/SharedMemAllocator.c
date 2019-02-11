/*
 *  @file       SharedMemAllocator.c
 *
 *  @brief      Shared Memory Allocator.
 *
 *  ============================================================================
 *
 *  Copyright (c) 2012, Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  *  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *  *  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 *  *  Neither the name of Texas Instruments Incorporated nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 *  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 *  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 *  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *  Contact information for paper mail:
 *  Texas Instruments
 *  Post Office Box 655303
 *  Dallas, Texas 75265
 *  Contact information:
 *  http://www-k.ext.ti.com/sc/technical-support/product-information-centers.htm?
 *  DCMP=TIHomeTracking&HQS=Other+OT+home_d_contact
 *  ============================================================================
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "ti/shmemallocator/SharedMemoryAllocatorUsr.h"

shm_buf bufs[100];
int shmblocks[2] = {0x1000000, 0x1000000};

void printMenu()
{
    printf("\n================================\n");
    printf("\n1 : req buffer(size, block, alignment)\n");
    printf("\n2 : req buffer(size, block)\n");
    printf("\n3 : req buffer(size, alignment)\n");
    printf("\n4 : req buffer(size)\n");
    printf("\n0 : release buffer\n");
    printf("\nC : release all buffers\n");
    printf("\n# : print allocated bufs\n");
    printf("\nR : RANDOM test\n");
    printf("\nT : MONKEY test\n");
    printf("\nM/m : print Menu\n");
    printf("\nE/e : EXIT\n");
    printf("\n================================\n");
}

void printAllocBufs()
{
    int i;
    for(i=0; i<100; i++)
        if(bufs[i].size)
            printf("%d)VA=0x%0x bl=%d size=0x%0x\n", i, (unsigned)bufs[i].vir_addr, bufs[i].blockID, bufs[i].size);
}

void clearSHM()
{
    int i;
    int status;
    for(i=0; i<100; i++)
        if(bufs[i].size) {
            status = SHM_release(&bufs[i]);
            if(!status) {
                shmblocks[bufs[i].blockID] += bufs[i].size;
                bufs[i].size = 0;
                bufs[i].vir_addr = NULL;
                bufs[i].phy_addr = NULL;
                bufs[i].blockID = -1;
            }
            else
                printf("\nclearSHM: cloudn't release buf(%d) 0x%x)\n", i, (unsigned)bufs[i].vir_addr);
        }
}

void monkeyTest()
{
    int i;
    int size;
    int blockID;
    int alignment;
    int status;

    for(i=0; i<100; i++) {
        switch(rand()%8) {
            case 0:
                size = rand();
                alignment = rand();
                status = SHM_alloc_aligned(size, alignment, &bufs[i]);
                printf("\n[APP] : SHM_alloc_aligned(%d, 0x%x): %s\n", size, alignment, status?"FAILED":"PASSED");
                if(!status)
                    shmblocks[bufs[i].blockID] -= bufs[i].size;
                if(rand()%2) {
                    status = SHM_release(&bufs[i]);
                    printf("\n[APP] : SHM_release(0x%x, %d): %s\n", (unsigned)bufs[i].vir_addr, bufs[i].blockID, status?"FAILED":"PASSED");
                    if(!status) {
                        shmblocks[bufs[i].blockID] += bufs[i].size;
                        bufs[i].size = 0;
                        bufs[i].vir_addr = NULL;
                        bufs[i].phy_addr = NULL;
                        bufs[i].blockID = -1;
                    }

                }
                break;
            case 1:
                size = rand()%0x1000;
                alignment = rand()%10000;
                status = SHM_alloc_aligned(size, alignment, &bufs[i]);
                printf("\n[APP] : SHM_alloc_aligned(%d, 0x%x): %s\n", size, alignment, status?"FAILED":"PASSED");
                if(!status)
                    shmblocks[bufs[i].blockID] -= bufs[i].size;
                if(rand()%2) {
                    status = SHM_release(&bufs[i]);
                    printf("\n[APP] : SHM_release(0x%x, %d): %s\n", (unsigned)bufs[i].vir_addr, bufs[i].blockID, status?"FAILED":"PASSED");
                    if(!status) {
                        shmblocks[bufs[i].blockID] += bufs[i].size;
                        bufs[i].size = 0;
                        bufs[i].vir_addr = NULL;
                        bufs[i].phy_addr = NULL;
                        bufs[i].blockID = -1;
                    }
                }
                break;
            case 2:
                size = rand();
                blockID = rand();
                alignment = rand();
                status = SHM_alloc_aligned_fromBlock(size, alignment, blockID, &bufs[i]);
                if(!status)
                    shmblocks[bufs[i].blockID] -= bufs[i].size;
                printf("\n[APP] : SHM_alloc_aligned_fromBlock(%d, 0x%x, %d): %s\n", size, alignment, blockID, status?"FAILED":"PASSED");
                if(rand()%2) {
                    status = SHM_release(&bufs[i]);
                    printf("\n[APP] : SHM_release(0x%x, %d): %s\n", (unsigned)bufs[i].vir_addr, bufs[i].blockID, status?"FAILED":"PASSED");
                    if(!status) {
                        shmblocks[bufs[i].blockID] += bufs[i].size;
                        bufs[i].size = 0;
                        bufs[i].vir_addr = NULL;
                        bufs[i].phy_addr = NULL;
                        bufs[i].blockID = -1;
                    }
                }
                break;
            case 3:
                size = rand()%0x1000;
                blockID = rand()%2;
                alignment = rand()%0xFFF;
                status = SHM_alloc_aligned_fromBlock(size, alignment, blockID, &bufs[i]);
                if(!status)
                    shmblocks[bufs[i].blockID] -= bufs[i].size;
                printf("\n[APP] : SHM_alloc_aligned_fromBlock(%d, 0x%x, %d): %s\n", size, alignment, blockID, status?"FAILED":"PASSED");
                if(rand()%2) {
                    status = SHM_release(&bufs[i]);
                    printf("\n[APP] : SHM_release(0x%x, %d): %s\n", (unsigned)bufs[i].vir_addr, bufs[i].blockID, status?"FAILED":"PASSED");
                    if(!status) {
                        shmblocks[bufs[i].blockID] += bufs[i].size;
                        bufs[i].size = 0;
                        bufs[i].vir_addr = NULL;
                        bufs[i].phy_addr = NULL;
                        bufs[i].blockID = -1;
                    }
                }
                break;
            case 4:
                size = rand();
                blockID = rand();
                status = SHM_alloc_fromBlock(size, blockID, &bufs[i]);
                if(!status)
                    shmblocks[bufs[i].blockID] -= bufs[i].size;
                printf("\n[APP] : SHM_alloc_fromBlock(%d, %d): %s\n", size, blockID, status?"FAILED":"PASSED");
                if(rand()%2) {
                    status = SHM_release(&bufs[i]);
                    printf("\n[APP] : SHM_release(0x%x, %d): %s\n", (unsigned)bufs[i].vir_addr, bufs[i].blockID, status?"FAILED":"PASSED");
                    if(!status) {
                        shmblocks[bufs[i].blockID] += bufs[i].size;
                        bufs[i].size = 0;
                        bufs[i].vir_addr = NULL;
                        bufs[i].phy_addr = NULL;
                        bufs[i].blockID = -1;
                    }
                }
                break;
            case 5:
                size = rand()%0x1000;
                blockID = rand()%2;
                status = SHM_alloc_fromBlock(size, blockID, &bufs[i]);
                printf("\n[APP] : SHM_alloc_fromBlock(%d, %d): %s\n", size, blockID, status?"FAILED":"PASSED");
                if(!status)
                    shmblocks[bufs[i].blockID] -= bufs[i].size;
                if(rand()%2) {
                    status = SHM_release(&bufs[i]);
                    printf("\n[APP] : SHM_release(0x%x, %d): %s\n", (unsigned)bufs[i].vir_addr, bufs[i].blockID, status?"FAILED":"PASSED");
                    if(!status) {
                        shmblocks[bufs[i].blockID] += bufs[i].size;
                        bufs[i].size = 0;
                        bufs[i].vir_addr = NULL;
                        bufs[i].phy_addr = NULL;
                        bufs[i].blockID = -1;
                    }
                }
                break;
            case 6:
                size = rand();
                blockID = rand();
                status = SHM_alloc(size, &bufs[i]);
                printf("\n[APP] : SHM_alloc(%d): %s\n", size, status?"FAILED":"PASSED");
                if(!status)
                    shmblocks[bufs[i].blockID] -= bufs[i].size;
                if(rand()%2) {
                    status = SHM_release(&bufs[i]);
                    printf("\n[APP] : SHM_release(0x%x, %d): %s\n", (unsigned)bufs[i].vir_addr, bufs[i].blockID, status?"FAILED":"PASSED");
                    if(!status) {
                        shmblocks[bufs[i].blockID] += bufs[i].size;
                        bufs[i].size = 0;
                        bufs[i].vir_addr = NULL;
                        bufs[i].phy_addr = NULL;
                        bufs[i].blockID = -1;
                    }
                }
                break;
            case 7:
                size = rand()%0x1000;
                blockID = rand()%2;
                status = SHM_alloc(size, &bufs[i]);
                printf("\n[APP] : SHM_alloc(%d): %s\n", size, status?"FAILED":"PASSED");
                if(!status)
                    shmblocks[bufs[i].blockID] -= bufs[i].size;
                if(rand()%2) {
                    status = SHM_release(&bufs[i]);
                    printf("\n[APP] : SHM_release(0x%x, %d): %s\n", (unsigned)bufs[i].vir_addr, bufs[i].blockID, status?"FAILED":"PASSED");
                    if(!status) {
                        shmblocks[bufs[i].blockID] += bufs[i].size;
                        bufs[i].size = 0;
                        bufs[i].vir_addr = NULL;
                        bufs[i].phy_addr = NULL;
                        bufs[i].blockID = -1;
                    }
                }
                break;
        }
    }
}

void randomTest()
{
    int i;
    int size;
    int blockID;
    int alignment;
    int status;
    shm_buf buf;

    for(i=1; i<3; i++) {
        size = rand();
        blockID = rand();
        alignment = rand();
        status = SHM_alloc_aligned(size, alignment, &buf);
        printf("\n[APP] : SHM_alloc_aligned(%d, 0x%x): %s\n", size, alignment, status?"FAILED":"PASSED");
        status = SHM_release(&buf);
        printf("\n[APP] : SHM_release(0x%x, %d): %s\n", (unsigned)buf.vir_addr, buf.blockID, status?"FAILED":"PASSED");
        status = SHM_alloc_fromBlock(size, blockID, &buf);
        printf("\n[APP] : SHM_alloc_fromBlock(%d, %d): %s\n", size, blockID, status?"FAILED":"PASSED");
        status = SHM_release(&buf);
        printf("\n[APP] : SHM_release(0x%x, %d): %s\n", (unsigned)buf.vir_addr, buf.blockID, status?"FAILED":"PASSED");
        status = SHM_alloc_aligned_fromBlock(size, alignment, blockID, &buf);
        printf("\n[APP] : SHM_alloc_aligned_fromBlock(%d, 0x%x, %d): %s\n", size, alignment, blockID, status?"FAILED":"PASSED");
        status = SHM_release(&buf);
        printf("\n[APP] : SHM_release(0x%x, %d): %s\n", (unsigned)buf.vir_addr, buf.blockID, status?"FAILED":"PASSED");
        status = SHM_alloc(size, &buf);
        printf("\n[APP] : SHM_alloc(%d): %s\n", size, status?"FAILED":"PASSED");
        status = SHM_release(&buf);
        printf("\n[APP] : SHM_release(0x%x, %d): %s\n", (unsigned)buf.vir_addr, buf.blockID, status?"FAILED":"PASSED");
        size = rand()%4096;
        blockID = rand()%2;
        alignment = rand()%(i*1000);
        status = SHM_alloc_aligned(size, alignment, &buf);
        printf("\n[APP] : SHM_alloc_aligned(%d, 0x%x): %s\n", size, alignment, status?"FAILED":"PASSED");
        status = SHM_release(&buf);
        printf("\n[APP] : SHM_release(0x%x, %d): %s\n", (unsigned)buf.vir_addr, buf.blockID, status?"FAILED":"PASSED");
        status = SHM_alloc_fromBlock(size, blockID, &buf);
        printf("\n[APP] : SHM_alloc_fromBlock(%d, %d): %s\n", size, blockID, status?"FAILED":"PASSED");
        status = SHM_release(&buf);
        printf("\n[APP] : SHM_release(0x%x, %d): %s\n", (unsigned)buf.vir_addr, buf.blockID, status?"FAILED":"PASSED");
        status = SHM_alloc_aligned_fromBlock(size, alignment, blockID, &buf);
        printf("\n[APP] : SHM_alloc_aligned_fromBlock(%d, 0x%x, %d): %s\n", size, alignment, blockID, status?"FAILED":"PASSED");
        status = SHM_release(&buf);
        printf("\n[APP] : SHM_release(0x%x, %d): %s\n", (unsigned)buf.vir_addr, buf.blockID, status?"FAILED":"PASSED");
        status = SHM_alloc(size, &buf);
        printf("\n[APP] : SHM_alloc(%d): %s\n", size, status?"FAILED":"PASSED");
        status = SHM_release(&buf);
        printf("\n[APP] : SHM_release(0x%x, %d): %s\n", (unsigned)buf.vir_addr, buf.blockID, status?"FAILED":"PASSED");
    }
}

int main()
{
    int status, i;
    int size, alignment, blockID;
    char ch;
    int ip = 1;
    printMenu();
    while(ip) {
        ch = getchar();
        switch(ch) {
            case '#':
                printAllocBufs();
                break;
            case 'R':
                randomTest();
                break;
            case 'T':
                monkeyTest();
                break;
            case 'E':
            case 'e':
                ip = 0;
                 break;
            case 'M':
            case 'm':
                printMenu();
                break;
            case 'C':
                clearSHM();
                break;
            case '1':
            case '2':
            case '3':
            case '4':
                for(i=0; i<100; i++) {
                    if(!bufs[i].vir_addr) {
                        printf("BUF[%d] selected\n", i);
                        break;
                    }
                }
                if(i==100) {
                    printf("\n###buf list full\n");
                    break;
                }
                if(ch == '1') {
                    printf("\nenter size(0x), alignment(0x), block(0x)\n");
                    scanf("%x, %x, %x", &size, &alignment, &blockID);
                    printf("\n0x%x, 0x%x, 0x%x\n", size, blockID, alignment);
                    fflush(stdin);
                    status = SHM_alloc_aligned_fromBlock(size, alignment, blockID, &(bufs[i]));
                } else if(ch == '2') {
                    printf("\nenter size(0x), block(0x)\n");
                    scanf("%x, %x", &size, &blockID);
                    printf("\n0x%x, 0x%x\n", size, blockID);
                    fflush(stdin);
                    status = SHM_alloc_fromBlock(size, blockID, &(bufs[i]));
                } else if(ch == '3') {
                    printf("\nenter size(0x), alignment(0x)\n");
                    scanf("%x, %x", &size, &alignment);
                    printf("\n0x%x, 0x%x\n", size, alignment);
                    fflush(stdin);
                    status = SHM_alloc_aligned(size, alignment, &(bufs[i]));
                } else {
                    printf("\nenter size(0x)\n");
                    scanf("%x", &size);
                    printf("\n%0x\n", size);
                    fflush(stdin);
                    status = SHM_alloc(size, &(bufs[i]));
                }
                if(!status) {
                    printf("\n[APP] : ALLOC REQ PASSED\n");
                    printf("\nsize=0x%x, addr=0x%x\n", bufs[i].size, (unsigned)bufs[i].vir_addr);
                    shmblocks[bufs[i].blockID] -= bufs[i].size;
                    printf("\nremainng block[0] = 0x%0x", shmblocks[0]);
                    printf("\nremainng block[1] = 0x%0x", shmblocks[1]);
                }
                else
                    printf("\n[APP] : ALLOC REQ FAILED\n");
                break;
            case '0':
                printAllocBufs();
                printf("\nEnter which buffer to be released:\n");
                scanf("%d", &i);
                if(i < 0 || i > 100)
                    printf("\nWRONG RELEASE ENTRY\n");
                else {
                    status = SHM_release(&bufs[i]);
                    if(!status) {
                        printf("\n[APP] : RELEASED REQ PASSED\n");
                        shmblocks[bufs[i].blockID] += bufs[i].size;
                        bufs[i].size = 0;
                        bufs[i].vir_addr = NULL;
                        bufs[i].phy_addr = NULL;
                        bufs[i].blockID = -1;
                        printf("\nremainng block[0] = 0x%0x", shmblocks[0]);
                        printf("\nremainng block[1] = 0x%0x", shmblocks[1]);
                    }
                    else
                        printf("\n[APP] : RELEASE REQ FAILED\n");
                }
                break;
        }
        if(ch != '\n' && ch != 'e' && ch != 'E')
            printMenu();
    }
    return 0;
}
