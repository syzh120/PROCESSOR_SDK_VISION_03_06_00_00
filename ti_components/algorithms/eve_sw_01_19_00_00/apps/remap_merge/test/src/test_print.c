/*
*
* Copyright (c) 2009-2017 Texas Instruments Incorporated
*
* All rights reserved not granted herein.
*
* Limited License.
*
* Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
* license under copyrights and patents it now or hereafter owns or controls to make,
* have made, use, import, offer to sell and sell ("Utilize") this software subject to the
* terms herein.  With respect to the foregoing patent license, such license is granted
* solely to the extent that any such patent is necessary to Utilize the software alone.
* The patent license shall not apply to any combinations which include this software,
* other than combinations with devices manufactured by or for TI ("TI Devices").
* No hardware patent is licensed hereunder.
*
* Redistributions must preserve existing copyright notices and reproduce this license
* (including the above copyright notice and the disclaimer and (if applicable) source
* code license limitations below) in the documentation and/or other materials provided
* with the distribution
*
* Redistribution and use in binary form, without modification, are permitted provided
* that the following conditions are met:
*
* *       No reverse engineering, decompilation, or disassembly of this software is
* permitted with respect to any software provided in binary form.
*
* *       any redistribution and use are licensed by TI for use only with TI Devices.
*
* *       Nothing shall obligate TI to provide you with source code for the software
* licensed and provided to you in object code.
*
* If software source code is provided to you, modification and redistribution of the
* source code are permitted provided that the following conditions are met:
*
* *       any redistribution and use of the source code, including any resulting derivative
* works, are licensed by TI for use only with TI Devices.
*
* *       any redistribution and use of any object code compiled from the source code
* and any resulting derivative works, are licensed by TI for use only with TI Devices.
*
* Neither the name of Texas Instruments Incorporated nor the names of its suppliers
*
* may be used to endorse or promote products derived from this software without
* specific prior written permission.
*
* DISCLAIMER.
*
* THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "remap_test_print.h"

uint16_t getARP32mhz(){

    return 250;
}

uint16_t getVCOPmhz(){

    return 500;

}

static float ratioVcopArp32;
static uint16_t testId;

void testPrintHeader(char *title){

    uint16_t arp32Mhz, vcopMhz;

    printf("               %s testing starts.\n", title);
    printf("               ARP32 freq: %d Mhz  VCOP freq: %d Mhz\n", arp32Mhz=getARP32mhz(), vcopMhz=getVCOPmhz());
    printf("------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| No | Status |Graph create| Graph init | Graph exec | Total exec | VCOP busy  | Description\n");
    printf("|    |        | ARP cycles | ARP cycles | cyc/point  | cyc/point  | cyc/point  |            \n");
    printf("------------------------------------------------------------------------------------------------------------------------------\n");

    testId= 0;
    ratioVcopArp32= (float)vcopMhz/arp32Mhz;
}

#define MAX_LINELEN  60
#define MAX_NUMLINES 5

void testPrintResults(int32_t errorFlag, uint64_t setupTimerDiff, uint32_t execGraphCycles,
                         uint64_t execTotalTimerDiff, uint64_t execVcopTimerDiff, char *desc, uint32_t size){

    uint16_t index, maxIndex;
    char *descString;
    char *curStr;
    char *line[MAX_NUMLINES+1];
    char *emptyString="";

    index= 1;

    if (desc== NULL) {
        descString= emptyString;
        line[0]= descString;
        }
    else {
        descString= desc;
/* Code below is to break up a long description string into multiple lines
   so everything fits nicely in the display.
   The algorithm looks for last space before the line exceeeds
   MAX_LINELEN int8_tacters to determine end of each line
   */
        curStr= descString;
        line[0]= descString;
        index= 1;
        while ((strlen(curStr) > MAX_LINELEN) && (index < MAX_NUMLINES)){
           curStr+= MAX_LINELEN;
           while (*curStr!= ' ' && curStr != descString)
              curStr--;
           if (curStr != descString)
              line[index++]= curStr;
           else
              line[index++]= descString + strlen(descString);
           curStr++;
        }

    }

    maxIndex= index;
    line[index]= descString + strlen(descString);

    index= 0;

    if (errorFlag == 0)
        printf("|%3d | PASS  ", testId++);
    else if (errorFlag == 1)
        printf("|%3d | FAIL  ", testId++);
    else if (errorFlag == 2)
        printf("|%3d | NO REF", testId++);

    *(line[index+1])= 0; // we set the end of line to '0'

    printf(" |%8lld    |%8lld    | %6.2f     | %6.2f     | %6.2f     | %s\n",
            (setupTimerDiff/(uint64_t)ratioVcopArp32),
            ((execTotalTimerDiff/(uint64_t)ratioVcopArp32) - execGraphCycles),
            (ratioVcopArp32*execGraphCycles)/size,
            ((float)execTotalTimerDiff)/size, ((float)execVcopTimerDiff)/size, line[0]);

    if (index != maxIndex - 1)
       *(line[index+1])= ' '; // we set back the end of line to ' ' if not last line
    index++;
    line[index]++; // advance pointer line[index] by 1 to skip the 0

    while (index != maxIndex) {
     *(line[index+1])= 0;
     printf("|    |        |            |            |            |            |            | %s\n", line[index]);
     if (index != maxIndex - 1)
       *(line[index+1])= ' ';
     index++;
     line[index]++; // advance pointer line[index] by 1 to skip the 0
    }
    printf("------------------------------------------------------------------------------------------------------------------------------\n");
}

void testPrintFooter(char *title){
    printf("------------------------------------------------------------------------------------------------------------------------------\n");
    printf("               %s testing ends\n\n", title);
}
